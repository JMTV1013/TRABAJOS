// Aquí defino el tamaño del tablero
const ancho = 15;
const alto = 10;

// Variables principales
let snake = [{ x: 5, y: 5 }];
let direccion = "DERECHA";
let nivel = 1;
let puntos = 0;
let comida = generarPosicion();
let trampa = generarPosicion();
let tamañoInicial = 5;

// Aquí agrego los primeros segmentos de la serpiente
for (let i = 1; i < tamañoInicial; i++) {
  snake.push({ x: 5 - i, y: 5 });
}

// Esta función genera una posición aleatoria
function generarPosicion() {
  return {
    x: Math.floor(Math.random() * ancho),
    y: Math.floor(Math.random() * alto)
  };
}

// Esta función dibuja el tablero con texto
function dibujarTablero() {
  console.clear();
  console.log("Nivel: " + nivel + " | Puntos: " + puntos);
  for (let y = 0; y < alto; y++) {
    let fila = "";
    for (let x = 0; x < ancho; x++) {
      if (x === comida.x && y === comida.y) fila += "C"; // comida
      else if (x === trampa.x && y === trampa.y) fila += "T"; // trampa
      else if (snake.some(s => s.x === x && s.y === y)) fila += "O"; // cuerpo
      else fila += ".";
    }
    console.log(fila);
  }
  console.log("Controles: W (arriba), S (abajo), A (izq), D (der), Q (salir)");
}

// Esta función mueve la serpiente
function moverSnake() {
  let cabeza = { ...snake[0] };

  // Muevo la cabeza según la dirección
  if (direccion === "ARRIBA") cabeza.y--;
  if (direccion === "ABAJO") cabeza.y++;
  if (direccion === "IZQUIERDA") cabeza.x--;
  if (direccion === "DERECHA") cabeza.x++;

  // Si sale del tablero, aparece del otro lado
  if (cabeza.x < 0) cabeza.x = ancho - 1;
  if (cabeza.x >= ancho) cabeza.x = 0;
  if (cabeza.y < 0) cabeza.y = alto - 1;
  if (cabeza.y >= alto) cabeza.y = 0;

  // Si choca consigo mismo, pierde
  for (let parte of snake) {
    if (parte.x === cabeza.x && parte.y === cabeza.y) {
      console.clear();
      console.log("Perdiste: chocaste contigo mismo.");
      process.exit();
    }
  }

  // Reviso si come o pisa trampa
  if (cabeza.x === comida.x && cabeza.y === comida.y) {
    puntos += 10;
    comida = generarPosicion();
  } else if (cabeza.x === trampa.x && cabeza.y === trampa.y) {
    snake.pop();
    trampa = generarPosicion();
  } else {
    snake.pop();
  }

  snake.unshift(cabeza);

  // Si se queda sin cuerpo, pierde
  if (snake.length === 0) {
    console.clear();
    console.log("Perdiste: te quedaste sin cuerpo.");
    process.exit();
  }

  // Si llega a tamaño 10, sube de nivel
  if (snake.length >= 10) {
    nivel++;
    console.log("Subiste al nivel " + nivel);
    snake = [];
    for (let i = 0; i < 10; i++) {
      snake.push({ x: i, y: 5 });
    }
    comida = generarPosicion();
    trampa = generarPosicion();
  }
}

// Esta función sirve para pedir texto al jugador
const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

// Aquí ejecuto el juego paso a paso pidiendo teclas
function pedirMovimiento() {
  dibujarTablero();
  readline.question("Movimiento: ", tecla => {
    let t = tecla.toUpperCase();

    if (t === "Q") {
      console.log("Juego terminado.");
      readline.close();
      return;
    }

    // Cambio la dirección según la tecla
    if (t === "W" && direccion !== "ABAJO") direccion = "ARRIBA";
    else if (t === "S" && direccion !== "ARRIBA") direccion = "ABAJO";
    else if (t === "A" && direccion !== "DERECHA") direccion = "IZQUIERDA";
    else if (t === "D" && direccion !== "IZQUIERDA") direccion = "DERECHA";

    moverSnake();

    // Sigo el juego repitiendo esta función
    pedirMovimiento();
  });
}

// Inicio del juego
console.clear();
console.log("Bienvenido al Snake simple");
pedirMovimiento();
