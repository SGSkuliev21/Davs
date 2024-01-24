import React, { useRef, useEffect } from 'react'; 
import NavBar from '../components/NavBar';
import Footer from '../components/Footer'
import { Link, Navigate } from "react-router-dom"
import 'react-lazy-load-image-component/src/effects/blur.css'; // Import the desired effect

function HomePage() {
  const section1Ref = useRef(null);
  const section2Ref = useRef(null);
  const section3Ref = useRef(null);



  const handleClick_section1 = () => {
    if (section1Ref.current) {
      section1Ref.current.scrollIntoView({ behavior: 'smooth' });
    }
  };
  const handleClick_section2 = () => {
    if (section2Ref.current) {
      section2Ref.current.scrollIntoView({ behavior: 'smooth' });
    }
  };
  const handleClick_section3 = () => {
    if (section3Ref.current) {
      section3Ref.current.scrollIntoView({ behavior: 'smooth' });
    }
  };
  const containerStyle = {
    textAlign: 'center',
    fontFamily: 'Arial, sans-serif',
  };
  
  return (
    <>
      <div style={containerStyle}>
        <NavBar handleClick={handleClick_section1} handleClick1={handleClick_section2} handleClick2={handleClick_section3}/>

        <div className='content-banner'>
          <div className='content-banner1'>
            <h1>Complete Solution For Your Education Needs!</h1>
            <Link to="/register"><button type="button">Register</button></Link>
          </div>
        </div>

          <div className="section-content">
            <div className="steps">
              <div className="steps-content">
                <p>STEP 1</p>
                <h3>REGISTER</h3>
              </div>
            </div>
            <div className="steps">
              <div className="steps-content">
                <p>STEP 2</p>
                <h3>MAKE REQUEST</h3>
              </div>
            </div>
            <div className="steps">
              <div className="steps-content">
                <p>STEP 3</p>
                <h3>GET YOUR WILL</h3>
              </div>
            </div>
          </div>
        
      
      <section className="section-2" ref={section1Ref} id="section-2">
        <div className="section__title">
          <h4>Features</h4>
          <h1>What does DAVS offer?</h1>
          <br></br>
          <hr></hr>
        </div>              
        <div className="section-content2">
          <br></br>
        </div>



      </section>
      
      <section className="section-3" ref={section2Ref}>
        <div className="section__title">

        </div>
      </section>
      
      <section className="section-1" ref={section3Ref} id="section-1">
        <div className="section__title">

        </div>
      </section>
      
      <Footer />  
    </div>
    </>
  );
}

export default HomePage;
