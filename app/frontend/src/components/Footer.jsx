function Footer() {
  const footerStyle = {
    backgroundColor: '#333',
    color: '#fff',
    padding: '1em',
    bottom: 0,
    width: '100%',
  };
  return (
    <footer style={footerStyle}>
      <p>&copy; {new Date().getFullYear()} DAVS. All rights reserved.</p>
    </footer>
  );
}
export default Footer;
