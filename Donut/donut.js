let donut_tag = document.getElementById('donut');
let A=0, B=0;
let draw = () => {
  let b=[];
  let z=[];
  A+=0.04;
  B+=0.02;
  let cA=Math.cos(A), sA=Math.sin(A),
      cB=Math.cos(B), sB=Math.sin(B);
  for (let k=0; 1761>k; k++) {
    b[k]=k%80==79 ? "\n" : " ";
    z[k]=0;
  }
  for (let j=0; 6.82>j; j+=0.004) {
    let ct=Math.cos(j), st=Math.sin(j);
    for (let i=0; 6.28>i; i+=0.035) {
      let sp=Math.sin(i), cp=Math.cos(i),
          h=ct+2, D=1/(sp*h*sA+st*cA+5), t=sp*h*cA-st*sA;
      let x=0 | (40+30*D*(cp*h*cB-t*sB)),
          y=0 | (12+15*D*(cp*h*sB+t*cB)),
          o=x+80*y,
          N=0|(8*((st*sA-sp*ct*cA)*cB-sp*ct*sA-st*cA-cp*ct*sB));
      if (22>y && y>=0 && 80>x && x>=0 && D>z[o]) {
        z[o]=D;
        b[o]=".,-~:;=!*#$@"[N>0 ? N : 0];        
      }
    }
  }
  donut_tag.innerHTML = b.join("");
};
let donut = () => {
  console.log("Donut running\n");
  setInterval(draw, 30);
}