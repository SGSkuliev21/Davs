import React, { useEffect, useState } from "react";
import ProfileP from "../assets/profile.png";
import { useNavigate } from 'react-router-dom';

const Profile = () => {
  const navigate = useNavigate();
  const [name, setName] = useState("");

  function handleLogout() {
    localStorage.removeItem('sb-bhxpjlxumnectpgwwlqv-auth-token');
    navigate('/');
  }

  useEffect(() => {
    const storedValue = localStorage.getItem('sb-bhxpjlxumnectpgwwlqv-auth-token');
    if (storedValue) {
      try {
        const parsedValue = JSON.parse(storedValue);
        const userValue = parsedValue.user;

        if (userValue && userValue.user_metadata.name) {
          const userName = userValue.user_metadata.name;
          setName(userName);
        } else {
          console.warn('User or name property not found in localStorage');
        }
      } catch (error) {
        console.error('Error parsing JSON:', error);
      }
    } else {
      console.warn('Value not found in localStorage');
    }
  }, []);

  return (
      <div className="main-profile">
        <div className="main-profile1">
          <div className='profile'>
            <img src={ProfileP} className="profile" alt="Profile Picture" />
            <h3>Welcome back, {name}</h3>
            <label></label>
            <button onClick={handleLogout}>Signout</button>

          </div>
        </div>
      </div>
  );
}

export default Profile;
