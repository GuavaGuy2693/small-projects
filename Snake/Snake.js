let snake_tag = document.getElementById('snake');
let dimension_tag = document.getElementsByClassName('item')[1]
let W=(dimension_tag.clientWidth)/8|0, H=(dimension_tag.clientHeight)/18|0,
    x, y, fx, fy, tn, tx = [null], ty = [null], dx, dy, dir;
let direction = {
  STOP  : Symbol("STOP"),
  UP    : Symbol("UP"),
  DOWN  : Symbol("DOWN"),
  LEFT  : Symbol("LEFT"),
  RIGHT : Symbol("RIGHT")
}
let Setup = () => {
  gameOver=false;
  dir=direction.STOP;
  x=W/2|0;y=H/2|0;
  fx=Math.random()*W|0;
  fy=Math.random()*H|0;
  tn=0;
}
let Draw = () => {
  let p = []
  for (let i=0; H>i; i++) {
    for (let j=0; W>j; j++) {
      if (j==x && i==y)
        p.push("O");
      else if (j==fx && i==fy)
        p.push("$");
      else {
        let tail=false;
        for (let k=0; k<tn; k++) {
          if (tx[k]==j&&ty[k]==i) {
            p.push("o");
            tail = true;
          }
        }
        if (!tail)
          p.push(" ");
      }
    }
    p.push("\n");
  }
  snake_tag.innerHTML = p.join("");
}
let Locate = () => {
  dx=Math.abs(fx-x)>Math.abs(W-x+fx) ? W-x+fx : fx-x,
  dy=Math.abs(fy-y)>Math.abs(W-y+fy) ? H-y+fy : fy-y;
}
let Input = () => {
  if (dx!=0) {
    if (dx<0) {
      dir = direction.LEFT;
    } if (dx>0)
      dir = direction.RIGHT;
  } if (dy!=0) {
    if (dy<0) 
      dir = direction.UP;
    if (dy>0)
      dir = direction.DOWN;   
  }
}
let Logic = () => {
  let px=tx[0], py=ty[0], p2x, p2y;
  tx[0]=x, ty[0]=y;
  for (let i=1;i<tn;i++) {
    p2x=tx[i];
    p2y=ty[i];
    tx[i]=px;
    ty[i]=py;
    px=p2x;
    py=p2y;
  }
  console.log(tx, ty, tn)
  switch (dir) {
    case direction.UP:
      if (dir!=direction.DOWN)
        y--;
      break;
    case direction.DOWN:
      if (dir!=direction.UP)
        y++;
      break;
    case direction.LEFT:
      if (dir!=direction.RIGHT)
        x--;
      break;
    case direction.RIGHT:
      if (dir!=direction.LEFT)
        x++;
      break;
    default:
      break;
  }
  if (x>=W) x=0; else if (x<0) x=W-1;
  if (y>=H) y=0; else if (y<0) y=H-1;
  if (x==fx && y==fy) {
    fx=Math.random()*W|0;
    fy=Math.random()*H|0;
    tn++;
  }
}
let Run = async () => {
  await Draw();
  await Logic();
  await Locate();
  await Input();
}
let snake = () => {
  Setup();
  console.log("Snake running\n");
  setInterval(Run, 60);
}