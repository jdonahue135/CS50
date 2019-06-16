import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    #get user id
    id = session.get("user_id")

    #get username and cash
    rows = db.execute("SELECT * FROM users WHERE id = :id", id=id)

    #get symbols and number of shares
    rows_portfolio = db.execute("SELECT symbol, sum(shares) FROM portfolio WHERE id = :id GROUP BY symbol", id=id)

    #get current value of symbol and add to table
    for row in rows_portfolio:
        symbol = row["symbol"]
        quote = lookup(symbol)
        price = quote["price"]
        row["price"] = price

    #get portfolio value
    total_price = rows[0]["cash"]
    for row in rows_portfolio:
        total_price = total_price + row["price"]*row["sum(shares)"]

    return render_template("index.html", rows=rows, rows_portfolio=rows_portfolio, total_price=total_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        #retrieve stock quote and number of shares
        symbol = request.form.get("symbol")

        #ensure symbol is valid
        quote = lookup(symbol)
        if not quote:
            return apology("Stock Symbol can't be found", 403)

        #ensure shares is valid interger
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("shares must be a positive integer", 400)

        #make sure user can afford stock
        id = session.get("user_id")
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
        cash = rows[0]["cash"]
        price = quote["price"]
        cost= shares*price
        if cash < cost:
            return apology("insufficient funds", 403)

        #log transaction and reduce cash for user
        else:
            db.execute(
                "INSERT INTO portfolio (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)",
                id=id,
                symbol=symbol,
                shares=shares,
                price=price)
            cash = cash-cost
            db.execute(
                "UPDATE users SET cash = :cash WHERE id=:id",
                id=id,
                cash=cash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    username = request.form.get("username")

    #check username length
    if not username:
        return jsonify(False)

    #query database for username
    else:
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if not rows:
            return jsonify(True)
        else:
            return jsonify(False)

@app.route("/history")
@login_required
def history():
    """"shows user transaction history"""

    id = session.get("user_id")
    rows = db.execute("SELECT * FROM portfolio WHERE id = :id", id=id)
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        #retrieve stock quote
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        #ensure stock is valid
        if not quote:
            return apology("Stock Symbol can't be found", 403)
        else:
            #display stock quote
            return render_template("stock.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirm password")

        #ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        #ensure passworde was submitted
        elif not password:
            return apology("must provide password", 403)

        #ensure confirm password was submitted
        elif not confirm_password:
            return apology("must confirm password", 403)

        #ensure password matches confirm password
        if password != confirm_password:
            return apology("password not confirmed", 403)

        # Query database for username
        result = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if not result:

            #encrypt password
            hash = generate_password_hash(password)

            #insert username and encrypted password into database
            db.execute(
                "INSERT INTO users (username, hash) VALUES (:username, :hash)",
                username=request.form.get("username"),
                hash=hash)

        # Remember which user has logged in
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    #get user id
    id = session.get("user_id")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        # Ensure shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        #retrieve stock quote and number of shares
        symbol = request.form.get("symbol")

        #ensure symbol is valid
        quote = lookup(symbol)
        if not quote:
            return apology("Stock Symbol can't be found", 403)

        #ensure shares is valid interger
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("shares must be a positive integer", 400)

        #ensure user owns enough shares of the stock to sell
        rows = db.execute("SELECT sum(shares) FROM portfolio WHERE id = :id AND symbol = :symbol GROUP BY symbol", id=id, symbol=symbol)
        owned_shares = rows[0]["sum(shares)"]
        if owned_shares < shares:
            return apology("insufficient shares", 400)
        else:
            #log sale of shares and update cash
            price = quote["price"]
            db.execute(
                "INSERT INTO portfolio (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)",
                id=id,
                symbol=symbol,
                shares=-shares,
                price=price)
            rows = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
            cash = shares*price + rows[0]["cash"]
            db.execute(
                "UPDATE users SET cash = :cash WHERE id=:id",
                id=id,
                cash=cash)

            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        #get users owned stocks
        rows = db.execute("SELECT symbol FROM portfolio WHERE id = :id GROUP BY symbol", id=id)

        return render_template("sell.html", rows=rows)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
