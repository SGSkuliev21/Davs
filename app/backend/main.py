from fastapi import FastAPI, Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer
from pydantic import BaseModel

app = FastAPI()

users_db = {'user1': {'password': 'password1'}, 'user2': {'password': 'password2'}}

class User(BaseModel):
    username: str

class UserInDB(User):
    password: str

class UserInLogin(User):
    password: str

def get_user(db, username: str):
    if username in db:
        user_dict = db[username]
        return UserInDB(**user_dict)
    return None

@app.post("/token")
async def login_for_access_token(form_data: UserInLogin):
    user_db = get_user(users_db, form_data.username)
    
    if user_db and user_db.password == form_data.password:
        return {"access_token": form_data.username, "token_type": "bearer"}

    raise HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Incorrect username or password",
        headers={"WWW-Authenticate": "Bearer"},
    )