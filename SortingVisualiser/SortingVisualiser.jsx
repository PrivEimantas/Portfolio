//import './SortingVisualizer/SortingVisualiser.css';
import React from 'react';
import './SortingVisualiser.css';
// Change this value for the speed of the animations.
const ANIMATION_SPEED_MS = 1;

// Change this value for the number of bars (value) in the array.
const NUMBER_OF_ARRAYS = 310;

// This is the main color of the array bars.
const PRIMARY_COLOR = 'turquoise';

// This is the color of array bars that are being compared throughout the animations.
const SECONDARY_COLOR = 'red';

export default class SortingVisualizer extends React.Component {
  constructor(props) {
    super(props);

    this.state = { // create array
      array: [],
    };
  }

  //when app first loads, reset array, check if its accessible
  componentDidMount()  {
    this.resetArray();
  }

  //creates the array
  resetArray() {
    const array = [];
    for (let i = 0; i < NUMBER_OF_ARRAYS; i++) {
      array.push(randomIntFromInterval(5, 730)); //if starts at 1, barely visible
    }

    this.setState({array}); //reset state for new array so it can have it
  }

  


  

  

  

  //map the array on screen

  
  render(){
    const {array} = this.state;
    return(
      <div classname="array-container">
        {array.map((value,idx)=>(
          <div className="array-bar" key={idx} style={{height:`${value}px` }}>
            {value}
          </div>
        ))}
      </div>
    );
  }
  
  

  /*
  render() {
    const {array} = this.state;

    return (
      <div className="array-container">
        {array.map((value, idx) => (
          <div
            className="array-bar"
            key={idx}
            style={{
              backgroundColor: PRIMARY_COLOR,
              height: `${value}px`,
            }}></div>
        ))}
        
        
          
        
      </div>
    );
  }
  */
  
  
  
}

 
function randomIntFromInterval(min, max) {
  // min and max included
  return Math.floor(Math.random() * (max - min + 1) + min);
}

function arraysAreEqual(arrayOne, arrayTwo) {
  if (arrayOne.length !== arrayTwo.length) return false;
  for (let i = 0; i < arrayOne.length; i++) {
    if (arrayOne[i] !== arrayTwo[i]) {
      return false;
    }
  }
  return true;
}