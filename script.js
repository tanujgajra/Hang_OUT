let word="",displayWord=[],attemptsLeft=6;
let currentDifficulty="",currentLevel=1,hintsLeft=2;
let soundOn=true;

/* SOUNDS */
const correctSound = new Audio("assets/sounds/correct.mp3");
const wrongSound = new Audio("assets/sounds/wrong.mp3");
const winSound = new Audio("assets/sounds/win.mp3");
const loseSound = new Audio("assets/sounds/lose.mp3");

/* WORDS */
const words={
easy:["cat","dog","sun"],
medium:["apple","chair","table"],
hard:["javascript","developer"]
};

/* PAGE CHANGE */
function changePage(h,s){
document.getElementById(h).classList.remove("active");
document.getElementById(s).classList.add("active");
}

function goToLogin(){changePage("welcomePage","loginPage");}

/* LOGIN */
function login(){
let name=document.getElementById("name").value;
if(name===""){alert("Enter name");return;}
document.getElementById("welcomeText").innerText="Welcome "+name;
changePage("loginPage","userPage");
setTimeout(()=>changePage("userPage","difficultyPage"),1500);
}

/* THEME */
function toggleTheme(){
document.body.classList.toggle("light");
}

/* SOUND */
function toggleSound(){
soundOn=!soundOn;
document.getElementById("soundBtn").innerText=
soundOn?"🔊 ON":"🔇 OFF";
}

/* DIFFICULTY */
function selectDifficulty(l){
currentDifficulty=l;
if(localStorage.getItem(l)===null) localStorage.setItem(l,1);
showLevels(l);
changePage("difficultyPage","levelPage");
}

/* LEVELS */
function showLevels(l){
let c=document.getElementById("levelsContainer");
c.innerHTML="";
let u=parseInt(localStorage.getItem(l));
if(isNaN(u)||u<1){u=1;localStorage.setItem(l,1);}
for(let i=1;i<=30;i++){
let b=document.createElement("button");
b.innerText=i;b.className="level-btn";
if(i>u)b.classList.add("locked");
b.onclick=function(){if(i<=u) startLevel(l,i);}
c.appendChild(b);
}
}

/* START LEVEL */
function startLevel(l,n){
currentDifficulty=l;currentLevel=n;
word=words[l][(n-1)%words[l].length];
displayWord=Array(word.length).fill("_");
attemptsLeft=6;hintsLeft=2;
document.getElementById("winPopup").classList.add("hidden");
document.getElementById("gameButtons").classList.add("hidden");
document.getElementById("hintBtn").style.display="inline-block";
updateDisplay();createKeyboard();changePage("levelPage","gamePage");
}

/* DISPLAY */
function updateDisplay(){
document.getElementById("wordDisplay").innerText=displayWord.join(" ");
document.getElementById("attempts").innerText=attemptsLeft;
document.getElementById("hintCount").innerText=hintsLeft;
document.getElementById("hangmanImg").src="assets/images/hangman"+(6-attemptsLeft)+".png";
}

/* KEYBOARD */
function createKeyboard(){
let k=document.getElementById("keyboard");k.innerHTML="";
for(let i=65;i<=90;i++){
let l=String.fromCharCode(i);
let b=document.createElement("button");
b.innerText=l;b.className="key";
b.onclick=()=>guess(l.toLowerCase(),b);
k.appendChild(b);}
}

/* GUESS */
function guess(l,b){
b.disabled=true;
if(word.includes(l)){
for(let i=0;i<word.length;i++) if(word[i]===l) displayWord[i]=l;
if(soundOn) correctSound.play();
}else{
attemptsLeft--;
if(soundOn) wrongSound.play();
}
updateDisplay();
checkGame();
}

/* HINT */
function useHint(){
if(hintsLeft<=0)return;
for(let i=0;i<word.length;i++){
if(displayWord[i]==="_"){displayWord[i]=word[i];break;}
}
hintsLeft--;
updateDisplay();
}

/* GAME CHECK */
function checkGame(){
if(!displayWord.includes("_")){
if(soundOn) winSound.play();
document.getElementById("winPopup").classList.remove("hidden");

/* UNLOCK NEXT LEVEL */
let u=parseInt(localStorage.getItem(currentDifficulty));
if(currentLevel>=u) localStorage.setItem(currentDifficulty,currentLevel+1);
}
else if(attemptsLeft===0){
if(soundOn) loseSound.play();
document.getElementById("keyboard").innerHTML="";
document.getElementById("hangmanImg").classList.add("hangman-big");
document.getElementById("gameButtons").classList.remove("hidden");
document.getElementById("hintBtn").style.display="none";
}
}

/* NEXT LEVEL */
function nextLevel(){
startLevel(currentDifficulty,currentLevel+1);
}

/* RETRY */
function retryLevel(){
startLevel(currentDifficulty,currentLevel);
}

/* HOME */
function goHome(){
changePage("gamePage","difficultyPage");
}

/* EXIT */
function exitGame(){
changePage("gamePage","welcomePage");
}

/* BACK BUTTONS */
function goBack(){changePage("gamePage","levelPage");}
function backToDifficulty(){changePage("levelPage","difficultyPage");}

/* CLOSE WIN POPUP */
function closePopup(){
document.getElementById("winPopup").classList.add("hidden");

/* ✅ REFRESH LEVEL BUTTONS TO SHOW UNLOCKED LEVEL */
showLevels(currentDifficulty); 

/* Stay in level page instead of going welcome */
changePage("gamePage","levelPage"); 
}