# banking_operations.py

def transfer(accounts):
    sender_account = int(input("Enter your account number (sender): "))
    receiver_account = int(input("Enter the account number of the recipient: "))
    amount = float(input("Enter the transfer amount: "))

    if sender_account in accounts and receiver_account in accounts:
        if accounts[sender_account]['balance'] >= amount:
            accounts[sender_account]['balance'] -= amount
            accounts[receiver_account]['balance'] += amount
            save_accounts(accounts)
            print("\nTransfer successful!")
            print(f"Your new balance is {accounts[sender_account]['balance']}")
        else:
            print("\nInsufficient funds. Transfer failed.")
    else:
        print("\nOne or both accounts not found. Please check account numbers.")

def create_account(accounts):
    name = input("Enter your name: ")
    balance = float(input("Enter initial balance: "))
    account_number = len(accounts) + 1

    accounts[account_number] = {
        'name': name,
        'balance': balance
    }

    print(f"\nAccount created successfully! Your account number is {account_number}\n")
