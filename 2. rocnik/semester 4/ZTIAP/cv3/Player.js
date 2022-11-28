class Player extends Character{
    constructor(Strenght, Health, Armor) {
        super(Strenght, Health, Armor)
    }
    Attack(enemy) {
        enemy.Health -= d6() + this.Strenght
    }

    getIsDead(player) {
        if (player.Health == 0 || player.Health < 0) {
            //console.log(player.Health)
            player.Health = 0;
            //console.log(player.Health)
            return 1;
        }
        else {
            return 0;
        }
    }
    
}