function d6(min, max) {
    min = 1;
    max = 6;
    return Math.floor(Math.random()*(max-min+1)+min);
}

function d20(min,max) {
    min = 1;
    max = 20;
    return Math.floor(Math.random()*(max-min+1)+min);    
}

//to do
//make the console.log to output into HTML <div>
//seperate files for classes: done
//prepare for MVC (seperate the vars and methods into model and controller, view is currently empty)
//canvas demo //code already in main function, not currently working
//MVC canvas, prob through the view class, idk how yet

function main() {
    Player.Health = d6();
    let player = new Player(5, 20, 10)
    let enemy = new Enemy(10, 26, 5)

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    ctx.clearRect(0,0,canvas.width, canvas.height);
    ctx.save();
        ctx.fillStyle=("rgba(255,0,0,1)");
        ctx.beginPath();
        ctx.arc(20,20,5,45,120,false);
        ctx.fill();
        //ctx.rect(20,20,150,100);
        //ctx.stroke();
    ctx.restore();
    

    while (player.getIsDead(player) == 0 && enemy.getIsDead(enemy) == 0) {
        player.Attack(enemy)
        if (enemy.getIsDead(enemy) == 0) {
            document.getElementById("log").innerHTML("Player attacked enemy!\nEnemy health remaining:"+enemy.Health+"\n-------------------------")
        }
        else {
            console.log("Enemy died!\nYou Win!");
            break;
        }
        enemy.Attack(player)
        if (player.getIsDead(player) == 0) {
            console.log("Enemy attacked player!\nPlayer health remaining:"+player.Health+"\n-------------------------")
        }
        else {
            console.log("Player died!\nYou lose!");
            break;
        }
    }
}

main()