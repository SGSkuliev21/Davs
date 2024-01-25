import React, { useState, useEffect } from "react";
import { Link, useNavigate } from "react-router-dom";
import { ToastContainer, toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import Footer from "../components/Footer";
import {supabase} from "../lib/helper/supabaseClient";

const Login = ({setToken}) => {


  let navigate = useNavigate()

  const [formData,setFormData] = useState({
        email:'',password:''
  })

  console.log(formData)

  function handleChange(event){
    setFormData((prevFormData)=>{
      return{
        ...prevFormData,
        [event.target.name]:event.target.value
      }

    })

  }

  async function handleSubmit(e){
    e.preventDefault()

    try {
        const { data, error } = await supabase.auth.signInWithPassword({
            email: formData.email,
            password: formData.password,
          })

      if (error) throw error
      console.log(data)
      setToken(data)
      navigate('/homepage')


    //   alert('Check your email for verification link')

      
    } catch (error) {
      alert(error)
    }
  }

  const loginform = async()=> {
    await supabase.auth.signInWithOAuth({
      provider:"github",
      options: {
        redirectTo: 'http://localhost:5173/main'
      }
    });
  }
  return (
    <>
      <div className="login-form">
        <div className="login-banner">
          <div className="login-banner1">
            <Link to="/"><i className="arrow"></i></Link>
              <label>
                <h2>Ctrl+S your digital legacy</h2>
                <br />
                <p>Draft a Digital Will for peace of mind.</p>
              </label>
          </div>
        </div>
      <div className="login-content">
          <div className="overlay">
            <div className="login-content1">
              <h1>Welcome Back!</h1>
              <p>Please login to continue.</p>
              <div className="auth-form">
                <h2>Login</h2>
                <form onSubmit={handleSubmit}>
                  <label>
                    <input
                      type="text"
                      placeholder="Email"
                      name='email'
                      onChange={handleChange}
                      />
                  </label>
                  <label>
                    <input
                      type="password"
                      placeholder="Password"
                      name='password'
                      onChange={handleChange}
                      />
                  </label>
                  <Link to="/register">
                    <p id="account">Don't you have an account?</p>
                  </Link>
                  <br />
                  <button onClick={loginform}>Login with Github</button>
                  <button type="submit">Login</button>
                </form>
              </div>
            </div>
          </div>
        </div>
        <Footer />
      </div>
    </>
  );
};

export default Login;
