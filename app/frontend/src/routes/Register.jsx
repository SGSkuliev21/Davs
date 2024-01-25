import { useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import axios from 'axios';
import Footer from '../components/Footer';
import { ToastContainer, toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import {supabase} from "../lib/helper/supabaseClient";


const Register = () => {
  const [formData,setFormData] = useState({
    fullName:'',email:'',password:''
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
      const { data, error } = await supabase.auth.signUp(
        {
          email: formData.email,
          password: formData.password,
          options: {
            data: {
              full_name: formData.fullName,
            }
          }
        }
      )
      if (error) throw error
      alert('Check your email for verification link')

      
    } catch (error) {
      alert(error)
    }
  }


  return (
    <>
      <div className="login-form">
        <div className="login-banner2">
          <div className="login-banner1">
            <Link to="/"><i className="arrow"></i></Link>
            <label>
              <h2>"Preserve your digital legacy with a click</h2>
              <br />
              <p>Your Digital Will, Your Lasting Impact</p>
            </label>
          </div>
        </div>
        <div className="login-content">
          <div className="overlay">
            <div className="register-content1">
              <label></label>
              <h1>Welcome!</h1>
              <p>Begin your journey now.</p>
              <div className="auth-form1">
                <h2>Registration</h2>
                <form onSubmit={handleSubmit}>
                  <label>
                    <input
                      type="text" 
                      placeholder="FullName"
                      name='fullName'
                      onChange={handleChange}
                    />
                  </label>
                  <label>
                    <input
                      type="email"
                      placeholder="Email"
                      className="input"
                      name='email'
                      onChange={handleChange}
                    />
                  </label>
                  <label>
                    <input
                      type="password"
                      placeholder="Password"
                      className="input"
                      name='password'
                      onChange={handleChange}
                    />
                  </label>
                  <br />
                  <button type="submit">
                    Register
                  </button>
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

export default Register;
