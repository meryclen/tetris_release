

const hoge = (() =>
{

console.log(window.innerHeight+"あ"+"i"+"\n"+"j");

const tes = 55;
console.log("tes"+" "+tes);
console.log("tes"+tes);

const quiz = [
    {
        question: "ゲーム史上、最も売れたゲームは？",
        answers: [
            "スーパーファミコン",
            "プレイステーション２",
            "ニンテンドースイッチ",
            "ニンテンドーＤＳ"
        ],
        correct: "ニンテンドーＤＳ"
    },
    {
        question: "ファイナルファンタジー４の主人公の名前は？",
        answers: [
            "クラウド",
            "フリオニール",
            "セシル",
            "シド"
        ],
        correct: "セシル"
    }
];

const quizLength = quiz.length;
let quizIndex = 0;
let score = 0;

const $button = document.getElementsByTagName("button");
const answersLength = quiz[quizIndex].answers.length;

const $question = document.getElementById("js-question");

const setupQuiz = () =>
{
    let count1 = 0;
    //while(count1 < answersLength)
    {
        $question.textContent = quiz[quizIndex].question;
    }


    count1 = 0;
    while(count1 < answersLength)
    {
        $button[count1].textContent = quiz[quizIndex].answers[count1];
        count1++;
    }
}




//func();

const func = ()=>
{
    console.log("testttt");

}

setupQuiz();

//func();

//const question = "テキストコンテンツ1";

/*
const answers =
[
    "スーパーファミコン",
    "プレイステーション２",
    "ニンテンドースイッチ",
    "ニンテンドーＤＳ"
]
*/

//const correct = "ニンテンドーＤＳ"; //3



//console.log("TagName div");
console.log(document.getElementsByTagName("div"));
console.log("ボタンタグは");
console.log(document.getElementsByTagName("button"));
console.log($button);
console.log("ID　question");
console.log();
console.log(document.getElementById("js-question"));

//document.getElementById("js-question").textContent = question;
console.log(document.getElementById("message").textContent)

//console.log("count: "+count);
//count = 0;
//console.log("count: "+count);

/*
//while(count < answers.length)
for(let count=0; count<answers.length; count++)
{
$button[count].addEventListener("click", () => {
    
    if(correct === count)
        window.alert("seikai");
    else
        window.alert("fuseikai");
        
});
//count++;
}
*/




const clickHandler = (e) =>
{
    if(quiz[quizIndex].correct === e.target.textContent)
    {
        document.getElementById("message").textContent = "メッセージ正解";
        //console.log("正解");
        window.alert("正解");
        //window.alert("quizIndex: "+quizIndex);
        //window.alert("quizLength: "+quizLength);
        score++;
    }
    else
    {
        //console.log("不正解");
        window.alert("不正解");
        //window.alert("quizLength: "+quizLength);
        //window.alert("quizIndex: "+quizIndex);

        //console.log("quizLength: "+quizLength);
        //console.log("quizIndex: "+quizIndex);
    }

    window.alert("quizIndex: "+quizIndex+" が終了しました");
    quizIndex++;
    
    //console.log("アラート前");

    if(quizIndex < quizLength)
        setupQuiz();
    else
    {
        //window
        window.alert("終了");
        window.alert("結果は "+score+" / "+quizLength+" でした");
        
        score = 0;
        quizIndex = 0;
        setupQuiz();
    }
};


for(let count=0; count<quiz[quizIndex].answers.length; count++)
{
$button[count].addEventListener("click", (e) => {
    console.log("クリックされた");
    clickHandler(e);
        
});
//count++;
}


});




const hoge1 = () =>
{
    const $doc = document;
    const $tab = $doc.getElementById("js-tab");
    console.log("tab: ",$tab);
    console.log("tbbb",$tab);
    console.log("tab: " + $tab);

    const $nav = $tab.querySelectorAll("[data-nav]");
    console.log("nav: ",$nav);

    const $content = $tab.querySelectorAll("[data-content]");
    console.log("content: ",$content);


    const init = () =>
    {
        $content[0].style.display = "block";
    };

    init();


/*
    document.addEventListener("DOMContentLoaded", () => {
        const $navnav = document.querySelectorAll("#navnav");
        console.log("$navnav: ", $navnav);
        console.log("$navnav[0]: ", $navnav[0]);
        $nav[0].addEventListener("click", (e) => {
            handleClick(e);
        });
    });
    
    const handleClick = (e) => {
        console.log("クリックされました");
        e.preventDefault();
    };
*/






    console.log("hoge!");

    
    console.log("$nav[0] ha ",$nav[0]);
    console.log("$nav ha ",$nav);

    
    console.log("$nav.length",$nav.length);


    
    const handleClick = (e) => {
        e.preventDefault();

        //console.log("e!",e);

        //クリックされたnavとそのdataを取得
        const $this = e.target;
        const targetVal = $this.dataset.nav;
        console.log("tagetVal: ",targetVal);

        //対象外のnav, content全て一旦リセットする
        let index = 0;
        while(index < $nav.length){
            $content[index].style.display = "none";
            $nav[index].classList.remove("is-active");
            index++;
        }

        //対象のコンテンツをアクティブ化する
        $tab.querySelectorAll('[data-content="'+targetVal+'"]')[0].style.display = "block";
        $nav[targetVal].classList.add("is-active");
        console.log("nav[targetVal].classList", $nav[targetVal].classList);

        console.log("結果: ",$nav);
    }


    let count = 0;
    while(count < $nav.length)
    {
        $nav[count].addEventListener("click", (e) => { handleClick(e);});
        count++;
    }
    

    //$nav[0].addEventListener("click", (e) => handleClick(e));




    //if($nav.length > 0)
    
    /*
    $tab.addEventListener("click", (e) => {
        console.log("gaseffwfweasef");
        e.preventDefault();
        console.log("gasefasef");
    });
    

    const handleClick = 
    () =>
    {
        console.log("くりっくされた");
        //console.log("くりっく１");
        //e.preventDefault();
        //console.log("くりっく",e);
        //console.log("hoge");
        //console.log("e: ",e);

    };

    handleClick();

    document.addEventListener("DOMContentLoaded", () => {
            //const $nav = document.querySelectorAll("#nav");
            console.log("$navあああ: ", $nav);
            console.log("$nav[0]いいいい: ", $nav[0]);

            /*
            $nav[0].addEventListener("click", (e) => {
                handleClick(e);
            });
        });
        
        
        */



    



};


//hoge();
hoge1();
