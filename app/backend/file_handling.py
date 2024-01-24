# file_handling.py
import json

def load_accounts():
    try:
        with open('accounts.json', 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        return {}

def save_accounts(accounts):
    with open('accounts.json', 'w') as file:
        json.dump(accounts, file, indent=2)
