import React, { useRef, useEffect } from 'react'; 
import NavBar from '../components/NavBar';
import Footer from '../components/Footer'
import { Link, Navigate } from "react-router-dom"
import 'react-lazy-load-image-component/src/effects/blur.css'; // Import the desired effect

function HomePage() {
  const section1Ref = useRef(null);
  const section2Ref = useRef(null);
  const section3Ref = useRef(null);

  const openGitHubRepository = () => {
    window.open('https://github.com/SGSkuliev21/Davs', '_blank');
  };

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
          <div className='content-banner2'>
          <div className='content-banner1'>
            <h1>Secure tomorrow's memories today with <span>DAVS</span></h1>
            <Link to="/register"><button type="button">Register</button></Link>
          </div>
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
                <h3>SECURE YOUR WILL</h3>
              </div>
            </div>
          </div>
        
      
      <section className="section-2" ref={section1Ref} id="section-2">
        <div className="section__title">
          <h4>Features</h4>
          <h1>What does DAVS Offer?</h1>
          <br></br>
          <hr></hr>
          <p>Digital Advanced Vitalization Systems (DAVS) revolutionize the concept of wills in the digital era, offering a seamless and secure platform for individuals to manage their digital assets and distribute them according to their wishes. DAVS provides a comprehensive solution for organizing and bequeathing online accounts, cryptocurrencies, social media profiles, and other digital possessions. </p>
        </div>              
        <div className="section-content2">
          <br></br>
        </div>
      </section>
      
      <section className="section-3" ref={section2Ref}>
        <div className="section__title">
          <h4>About</h4>
          <h1>About Our Organization</h1>
          <br></br>
          <hr></hr>
          <p>Welcome to our organization! We are a dynamic team of four students currently studying at the Virtual School of Creative and Performing Arts (VSCPI). Our collaboration is rooted in a shared commitment to academic excellence, creativity, and personal growth. Through our diverse skills and backgrounds, we aim to make a positive impact in our respective fields. Join us on this exciting journey where the unique experiences and talents of four VSCPI students converge to shape the narrative of our organization.
</p>
        </div>
      </section>
      
      <section className="section-1" ref={section3Ref} id="section-1">
        <div className="section__title">
          <h4>Download</h4>
          <h1>How to Download Our Application?</h1>
          <br></br>
          <hr></hr>
          <p>To download a file or software, follow these simple steps. Begin by visiting the official website or trusted source where the item is available. Once on the website, locate the designated download section or button, which is typically labeled as "Download" or something similar.</p>
         <button type="button" onClick={openGitHubRepository}>Donwload</button>
        </div>
      </section>
      
      <Footer />  
    </div>
    </>
  );
}

export default HomePage;
