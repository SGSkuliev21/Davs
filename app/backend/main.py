# main.py
from banking_operations import create_account, deposit, withdraw, check_balance, transfer, load_accounts, save_accounts

def main():
    accounts = load_accounts()

    while True:
        print("Welcome to the Banking System")
        print("1. Create Account")
        print("2. Deposit")
        print("3. Withdraw")
        print("4. Transfer")
        print("5. Check Balance")
        print("6. Exit")

        choice = input("Enter your choice (1-6): ")

        if choice == '1':
            create_account(accounts)
        elif choice == '2':
            deposit(accounts)
        elif choice == '3':
            withdraw(accounts)
        elif choice == '4':
            transfer(accounts)
        elif choice == '5':
            check_balance(accounts)
        elif choice == '6':
            print("Exiting the program. Thank you!")
            save_accounts(accounts)
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 6.")

if __name__ == "__main__":
    main()
