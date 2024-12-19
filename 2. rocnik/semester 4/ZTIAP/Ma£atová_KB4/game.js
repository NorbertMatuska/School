const canvas = document.querySelector('canvas')
const ctx = canvas.getContext('2d')
const gameover = document.getElementById('gameover');
const first_level = document.getElementById('playfield');
const levels = document.getElementById('levels');
const Menu = document.getElementById('Menu');
const retryButton = document.getElementById('retryButton');
const startButton = document.getElementById('startButton');
const optionsbutton = document.getElementById('optionsbutton');
const homeButton = document.getElementById('homeButton');
const level1 = document.getElementById('level1');
const sound = document.getElementById('sound');
const modalIMenu = document.getElementById('modalIMenu');
const backButton = document.getElementById('backButton');



window.onload = () => {
  modalIMenu.style.display = 'none';
  //Menu.style.display = 'flex';
}

let isPlaying = false;

/*function rectangle() {
  ctx.fillStyle = 'yellow'
  ctx.fillRect (0,0,50,50)
}*/

addEventListener('click', (event) => {
  clicks.push(new Click(
    event.clientX,
    event.clientY,
    5,
    'black' // TODO urcit farbu "neviditelna"
  ))
})

//------------------------------------------------------------------BUTTONS-------------------------------------------------------------------
startButton.addEventListener('click', () => {
  Menu.style.display = 'none'
  gameover.style.display = 'none'
  modalIMenu.style.display = 'none'
  levels.style.display = 'flex'
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