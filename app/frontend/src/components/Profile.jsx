import React, { Component } from "react";
import ProfileP from "../assets/profile.png";
import {Link} from "react-router-dom"
import { useNavigate } from 'react-router-dom'



const Profile = ({token}) => {
  let navigate = useNavigate()
  
  function handleLogout(){
    sessionStorage.removeItem('token')
    navigate('/')
  }
    
  return (
      <>
        <div className="main-profile">
          <div className="main-profile1">
            <div className='profile'>
              <img src={ProfileP} className="profile" alt="Profile Picture" />
              <h3>Welcome back, {}</h3>
              <button onClick={handleLogout}>Signout</button>
            </div>
          </div>
        </div>
      </>
    );
}

export default Profile;
