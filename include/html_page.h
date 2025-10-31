#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include <Arduino.h>

// Web interface HTML
const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html><html lang="en"><head>
<meta charset="utf-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>Sims Plumbob Control</title>
<style>
:root{
  --bg:#0a0e1a;
  --card:#12172e;
  --card-hover:#1a2140;
  --txt:#e8f0ff;
  --mut:#7a8fb3;
  --accent:#34C759;
}
body{
  font-family:-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Oxygen,Ubuntu,sans-serif;
  background:linear-gradient(135deg,#0a0e1a 0%,#1a1f3a 100%);
  color:var(--txt);
  margin:0;
  padding:20px;
  min-height:100vh;
  display:flex;
  align-items:center;
  justify-content:center;
}
.wrap{
  max-width:680px;
  width:100%;
}
.card{
  background:var(--card);
  padding:32px;
  border-radius:24px;
  box-shadow:0 20px 60px rgba(0,0,0,.5),0 0 1px rgba(255,255,255,.1) inset;
  backdrop-filter:blur(10px);
}
.header{
  text-align:center;
  margin-bottom:32px;
}
.header h1{
  font-size:2rem;
  margin:0 0 8px;
  font-weight:700;
  background:linear-gradient(135deg,#34C759,#2DD6C1);
  -webkit-background-clip:text;
  -webkit-text-fill-color:transparent;
  background-clip:text;
}
.header p{
  margin:0;
  color:var(--mut);
  font-size:0.95rem;
}
.section-title{
  font-size:0.85rem;
  text-transform:uppercase;
  letter-spacing:1px;
  color:var(--mut);
  margin:0 0 16px;
  font-weight:600;
}
.grid{
  display:grid;
  grid-template-columns:repeat(auto-fit,minmax(140px,1fr));
  gap:12px;
  margin-bottom:24px;
}
.mood-btn{
  border:2px solid transparent;
  border-radius:16px;
  padding:20px 16px;
  font-weight:600;
  font-size:1rem;
  cursor:pointer;
  color:#0a0e1a;
  transition:all 0.2s ease;
  box-shadow:0 4px 12px rgba(0,0,0,.3);
  position:relative;
  overflow:hidden;
}
.mood-btn:hover{
  transform:translateY(-2px);
  box-shadow:0 8px 20px rgba(0,0,0,.4);
  border-color:rgba(255,255,255,.3);
}
.mood-btn:active{
  transform:translateY(0);
  box-shadow:0 2px 8px rgba(0,0,0,.3);
}
.mood-btn::before{
  content:'';
  position:absolute;
  top:0;
  left:0;
  right:0;
  bottom:0;
  background:linear-gradient(135deg,rgba(255,255,255,.2),rgba(255,255,255,0));
  opacity:0;
  transition:opacity 0.2s ease;
}
.mood-btn:hover::before{
  opacity:1;
}
.footer{
  text-align:center;
  margin-top:24px;
  padding-top:24px;
  border-top:1px solid rgba(255,255,255,.1);
}
.status{
  display:inline-flex;
  align-items:center;
  gap:8px;
  padding:8px 16px;
  background:rgba(52,199,89,.15);
  border:1px solid rgba(52,199,89,.3);
  border-radius:999px;
  color:var(--accent);
  font-size:0.9rem;
  font-weight:500;
}
.status-dot{
  width:8px;
  height:8px;
  background:var(--accent);
  border-radius:50%;
  animation:pulse 2s ease-in-out infinite;
}
@keyframes pulse{
  0%,100%{opacity:1;}
  50%{opacity:0.4;}
}
.control-row{
  display:flex;
  align-items:center;
  justify-content:space-between;
  padding:16px;
  background:rgba(255,255,255,.03);
  border-radius:12px;
  margin-bottom:12px;
  border:1px solid rgba(255,255,255,.05);
}
.control-label{
  font-weight:600;
  font-size:0.95rem;
  color:var(--txt);
}
.control-input{
  display:flex;
  align-items:center;
  gap:12px;
}
input[type="color"]{
  width:60px;
  height:40px;
  border:2px solid rgba(255,255,255,.2);
  border-radius:8px;
  cursor:pointer;
  background:transparent;
}
input[type="color"]::-webkit-color-swatch-wrapper{
  padding:4px;
}
input[type="color"]::-webkit-color-swatch{
  border:none;
  border-radius:4px;
}
input[type="range"]{
  width:180px;
  height:6px;
  border-radius:3px;
  background:rgba(255,255,255,.1);
  outline:none;
  -webkit-appearance:none;
}
input[type="range"]::-webkit-slider-thumb{
  -webkit-appearance:none;
  appearance:none;
  width:18px;
  height:18px;
  border-radius:50%;
  background:var(--accent);
  cursor:pointer;
  box-shadow:0 2px 8px rgba(52,199,89,.4);
}
input[type="range"]::-moz-range-thumb{
  width:18px;
  height:18px;
  border-radius:50%;
  background:var(--accent);
  cursor:pointer;
  border:none;
  box-shadow:0 2px 8px rgba(52,199,89,.4);
}
.brightness-val{
  min-width:35px;
  text-align:center;
  font-weight:600;
  color:var(--accent);
  font-size:0.95rem;
}
select{
  padding:8px 32px 8px 12px;
  background:rgba(255,255,255,.08);
  border:1px solid rgba(255,255,255,.15);
  border-radius:8px;
  color:var(--txt);
  font-size:0.95rem;
  font-weight:500;
  cursor:pointer;
  outline:none;
  appearance:none;
  background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='12' height='12' viewBox='0 0 12 12'%3E%3Cpath fill='%23e8f0ff' d='M6 9L1 4h10z'/%3E%3C/svg%3E");
  background-repeat:no-repeat;
  background-position:right 10px center;
}
select:hover{
  background:rgba(255,255,255,.12);
  border-color:rgba(255,255,255,.25);
}
.btn-apply{
  padding:8px 20px;
  background:linear-gradient(135deg,var(--accent),#2DD6C1);
  border:none;
  border-radius:8px;
  color:#0a0e1a;
  font-weight:600;
  font-size:0.9rem;
  cursor:pointer;
  transition:all 0.2s ease;
  box-shadow:0 2px 8px rgba(52,199,89,.3);
}
.btn-apply:hover{
  transform:translateY(-1px);
  box-shadow:0 4px 12px rgba(52,199,89,.4);
}
.btn-apply:active{
  transform:translateY(0);
}
@media(max-width:600px){
  .grid{grid-template-columns:repeat(auto-fit,minmax(120px,1fr));}
  .card{padding:24px;}
  .header h1{font-size:1.6rem;}
  .control-row{flex-direction:column;align-items:flex-start;gap:12px;}
  .control-input{width:100%;}
  input[type="range"]{width:100%;}
}
</style>
</head><body>
<div class="wrap">
  <div class="card">
    <div class="header">
      <h1>💎 Plumbob Control</h1>
      <p>Select your Sim's mood</p>
    </div>
    
    <div class="section-title">Mood States</div>
    <div class="grid" id="moods"></div>
    
    <div class="section-title" style="margin-top:32px">Advanced Controls</div>
    
    <div class="control-row">
      <div class="control-label">🎨 Custom Color</div>
      <div class="control-input">
        <input type="color" id="picker" value="#00FF00"/>
        <button class="btn-apply" id="apply">Apply</button>
      </div>
    </div>
    
    <div class="control-row">
      <div class="control-label">💡 Brightness</div>
      <div class="control-input">
        <input type="range" id="brightness" min="0" max="100" value="50"/>
        <span id="bval" class="brightness-val">50%</span>
      </div>
    </div>
    
    <div class="control-row">
      <div class="control-label">✨ Animation</div>
      <div class="control-input">
        <select id="anim">
          <option value="solid">Solid</option>
          <option value="pulse">Pulse</option>
        </select>
        <button class="btn-apply" id="saveAnim">Apply</button>
      </div>
    </div>
    
    <div class="footer">
      <div class="status">
        <span class="status-dot"></span>
        Two synchronized LED strips
      </div>
    </div>
  </div>
</div>
<script>
const moods=[
  {k:"happy",label:"😊 Happy",hex:"#00FF00"},
  {k:"inspired",label:"✨ Inspired",hex:"#2DD6C1"},
  {k:"focused",label:"🎯 Focused",hex:"#0A84FF"},
  {k:"confident",label:"💪 Confident",hex:"#FF9500"},
  {k:"playful",label:"🎮 Playful",hex:"#AF52DE"},
  {k:"flirty",label:"💋 Flirty",hex:"#FF2D55"},
  {k:"sad",label:"😢 Sad",hex:"#0B3D91"},
  {k:"angry",label:"😠 Angry",hex:"#FF3B30"},
  {k:"uncomfortable",label:"😰 Uncomfortable",hex:"#FFD60A"},
  {k:"tense",label:"😬 Tense",hex:"#FFB300"},
  {k:"fine",label:"😐 Fine",hex:"#FFFFFF"},
];
const grid=document.getElementById('moods');
moods.forEach(m=>{
  const b=document.createElement('button');
  b.className='mood-btn';
  b.textContent=m.label;
  b.style.background=m.hex;
  b.onclick=()=>{
    fetch(`/set?mood=${m.k}`)
      .then(()=>{
        b.style.transform='scale(0.95)';
        setTimeout(()=>b.style.transform='',100);
      })
      .catch(e=>console.error('Error:',e));
  };
  grid.appendChild(b);
});

const picker=document.getElementById('picker');
const brightness=document.getElementById('brightness');
const bval=document.getElementById('bval');
const anim=document.getElementById('anim');

let brightnessTimeout;
brightness.addEventListener('input',()=>{
  bval.textContent=brightness.value+'%';
  clearTimeout(brightnessTimeout);
  brightnessTimeout=setTimeout(()=>{
    const val255=Math.round(brightness.value*2.55);
    fetch(`/set?brightness=${val255}`)
      .then(()=>console.log('Brightness:',brightness.value+'%'))
      .catch(e=>console.error('Error:',e));
  },150);
});

document.getElementById('apply').onclick=()=>{
  const hex=picker.value.replace("#","");
  fetch(`/set?hex=${hex}`)
    .then(()=>{
      console.log('Color applied:',hex);
    })
    .catch(e=>console.error('Error:',e));
};

document.getElementById('saveAnim').onclick=()=>{
  fetch(`/set?anim=${anim.value}`)
    .then(()=>{
      console.log('Animation:',anim.value);
    })
    .catch(e=>console.error('Error:',e));
};
</script>
</body></html>
)HTML";

#endif // HTML_PAGE_H

