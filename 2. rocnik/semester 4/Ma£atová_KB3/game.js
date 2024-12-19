const canvas = document.querySelector('canvas')
const c = canvas.getContext('2d')
const gameover = document.getElementById('gameover');
const Menu = document.getElementById('Menu');
const retryButton = document.getElementById('retryButton');
const startButton = document.getElementById('startButton');
const optionsbutton = document.getElementById('optionsbutton');
const homeButton = document.getElementById('homeButton');
const sound = document.getElementById('sound');
const modalIMenu = document.getElementById('modalIMenu');
const backButton = document.getElementById('backButton');


window.onload = () => {
  modalIMenu.style.display = 'none';
}


let isPlaying = false;

addEventListener('click', (event) => {
  clicks.push(new Click(
    event.clientX,
    event.clientY,
    5,
    'black' 
  ))
})


  
startButton.addEventListener('click', () => {
  Menu.style.display = 'none'
  gameover.style.display = 'flex'
  modalIMenu.style.display = 'none'
})

optionsbutton.addEventListener('click', () => {
  Menu.style.display = 'none'
  gameover.style.display = 'none'
  modalIMenu.style.display = 'flex'
})



homeButton.addEventListener('click', () => {
  Menu.style.display = 'flex'
  gameover.style.display = 'none';
})

backButton.addEventListener('click', () => {
  modalIMenu.style.display = 'none'
  Menu.style.display = 'flex'
  gameover.style.display = 'none';
})

function play() {
  isPlaying ? sound.pause() : sound.play();
} 

sound.onplaying = function() {
  isPlaying = true;
};
sound.onpause = function() {
  isPlaying = false;
};

