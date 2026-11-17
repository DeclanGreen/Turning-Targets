import Module from 'manifold-3d';
import fs from 'fs';
const wasm = await Module(); wasm.setup();
const {Manifold} = wasm;
const box=(x,y,z,w,d,h)=>Manifold.cube([w,d,h]).translate([x,y,z]);
const cyl=(x,y,z,h,r,seg=48)=>Manifold.cylinder(h,r,r,seg).translate([x,y,z]);
const union=a=>Manifold.union(a), diff=(a,b)=>Manifold.difference(a,Array.isArray(b)?union(b):b);

// ---- parameters (mm) ----
const W=186, D=126, WALL=3, BASEH=55, LIDT=3;
const IX=WALL, IY=WALL; // inner origin
const inn=(x,y)=>[IX+x,IY+y];
const BTN_D=12.5, LED_D=5.3;

// ---- BASE ----
let base=box(0,0,0,W,D,BASEH);
base=diff(base, box(WALL,WALL,3,W-2*WALL,D-2*WALL,BASEH));
const adds=[];
// corner screw posts
const posts=[[5,5],[175,5],[5,115],[175,115]];
for(const [x,y] of posts){const [px,py]=inn(x,y); adds.push(cyl(px,py,3,BASEH-3,4.5));}
// Arduino Uno standoffs (board origin inner 4,14)
const ard=[[13.97,2.54],[15.24,50.8],[66.04,7.62],[66.04,35.56]];
for(const [x,y] of ard){const [px,py]=inn(4+x,14+y); adds.push(cyl(px,py,3,6,3.2));}
// retaining-rim pockets for other boards
const pocket=(x,y,w,d,h=4)=>{const [px,py]=inn(x,y);
  return diff(box(px-1.4,py-1.4,3,w+2.8,d+2.8,h), box(px,py,2,w,d,h+2));};
adds.push(pocket(80,8,50,26));   // relay module
adds.push(pocket(80,44,43,21));  // buck converter
adds.push(pocket(140,8,21,21));  // DFPlayer Mini
adds.push(pocket(140,40,20,16)); // amp
base=union([base,...adds]);
const cuts=[];
for(const [x,y] of posts){const [px,py]=inn(x,y); cuts.push(cyl(px,py,BASEH-12,13,1.4,24));}
for(const [x,y] of ard){const [px,py]=inn(4+x,14+y); cuts.push(cyl(px,py,3,7,1.4,24));}
// left wall: Arduino USB-B + barrel jack cutouts
cuts.push(box(-1,IY+14+38.1-8,3+6+1.6-1,WALL+2,16,14));
cuts.push(box(-1,IY+14+7.5-7,3+6+1.6-1,WALL+2,14,13));
// rear wall: DC input jack + relay output cable gland
cuts.push(cyl(0,0,0,WALL+2,5.6).rotate([-90,0,0]).translate([150,D-WALL-1,25]));
cuts.push(cyl(0,0,0,WALL+2,6.2).rotate([-90,0,0]).translate([100,D-WALL-1,25]));
base=diff(base,cuts);

// ---- LID ----
let lid=box(0,0,0,W,D,LIDT);
const lc=[];
// screw holes
for(const [x,y] of posts){const [px,py]=inn(x,y); lc.push(cyl(px,py,-1,LIDT+2,1.7,24)); lc.push(cyl(px,py,-1,2.2,3.2,24));}
// LCD window 71x24 centred (62,100) + 4 mount holes (75x31)
const lcx=62,lcy=100;
lc.push(box(lcx-35.5,lcy-12,-1,71,24,LIDT+2));
for(const dx of[-37.5,37.5])for(const dy of[-15.5,15.5])lc.push(cyl(lcx+dx,lcy+dy,-1,LIDT+2,1.7,24));
// 5 buttons
for(let i=0;i<5;i++)lc.push(cyl(28+i*32.5,42,-1,LIDT+2,BTN_D/2));
// 6 LEDs
for(let i=0;i<6;i++)lc.push(cyl(22+i*28.4,16,-1,LIDT+2,LED_D/2,32));
// speaker grille: hex pattern of 3mm holes inside r=20 at (145,95)
const sx=145,sy=90;
for(let r=-4;r<=4;r++)for(let c=-4;c<=4;c++){
  const x=sx+c*5.5+(r%2?2.75:0), y=sy+r*4.76;
  if(Math.hypot(x-sx,y-sy)<=19)lc.push(cyl(x,y,-1,LIDT+2,1.5,16));}
lid=diff(lid,lc);
// speaker locating ring under lid (ID 58)
const ring=diff(cyl(sx,sy,LIDT-0.01,3,31),cyl(sx,sy,LIDT-1,5,29));
lid=union([lid,ring]);
// flip so the outside face prints down? keep flat: lid outer face at z=0 -> print face-down.
function stl(m,name){
  const me=m.getMesh(); const v=me.vertProperties, t=me.triVerts, n=me.numProp;
  const L=['solid '+name];
  for(let i=0;i<t.length;i+=3){
    const p=[0,1,2].map(k=>[v[t[i+k]*n],v[t[i+k]*n+1],v[t[i+k]*n+2]]);
    const u=[p[1][0]-p[0][0],p[1][1]-p[0][1],p[1][2]-p[0][2]],w=[p[2][0]-p[0][0],p[2][1]-p[0][1],p[2][2]-p[0][2]];
    let nx=u[1]*w[2]-u[2]*w[1],ny=u[2]*w[0]-u[0]*w[2],nz=u[0]*w[1]-u[1]*w[0];const l=Math.hypot(nx,ny,nz)||1;
    L.push(`facet normal ${nx/l} ${ny/l} ${nz/l}\nouter loop`);
    for(const q of p)L.push(`vertex ${q[0]} ${q[1]} ${q[2]}`);
    L.push('endloop\nendfacet');
  }
  L.push('endsolid '+name); fs.writeFileSync(name+'.stl',L.join('\n'));
  console.log(name,'tris',t.length/3,'volume',m.volume().toFixed(0),'genus',m.genus(), 'bbox',JSON.stringify(m.boundingBox()));
}
stl(base,'turning-targets-base'); stl(lid,'turning-targets-lid');
