# Expense Tracker App

Create an app to manage personal finances.

The proposed solution should easily record personal financial transactions, generate spending reports, generate daily/weekly/monthly financial reports.


# Initial requirements
- Sign up 
- Login
- Update/View profile
- Reset password via email
- Get a list of transactions within a selected period of time
- Create/Read/Update/Delete transaction 
- Generate daily/weekly/monthly report
- Export reports in a file


# Expectation
- Telegram bot
- SQL storage
- All features

# Stage 1. Proof Of Concept
- Console app
- Use files as data storage
- No reset password
- No update profile
- No export in files
- No reports

# Domain entities
- user
- transaction

# Rules
- The expense transaction is a transaction where the amount is less than zero.
- The profit transaction is a transaction where the amount is more than OR equal to zero.

