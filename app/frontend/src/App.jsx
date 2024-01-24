
import Login from "./routes/Login.jsx";
import Register from "./routes/Register.jsx";
import React from "react";
import HomePage from "./routes/Home.jsx";
import MainPage from "./routes/MainPage.jsx";
import {createBrowserRouter, createRoutesFromElements, Route} from "react-router-dom"


const App = createBrowserRouter(
  
  createRoutesFromElements(
    <>
      <Route path="/" element={<HomePage/>} />
      <Route path="/login" element={<Login/>} />
      <Route path="/register" element={<Register/>} /> 
      <Route path="/main" element={<MainPage/>} /> 
    </>
  )
);

export default App;
