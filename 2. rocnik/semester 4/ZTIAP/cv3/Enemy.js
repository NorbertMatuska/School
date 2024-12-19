class Enemy extends Character{
    constructor(Strenght, Health, Armor) {
        super(Strenght, Health, Armor)
    }
    Attack(player) {
        if (player.Armor + 10 < d20() + this.Strenght) {
            player.Health -= d6() + this.Strenght
        }
    }
    getIsDead(enemy) {
        if (enemy.Health == 0 || enemy.Health <0) {
            enemy.Health = 0;
            return 1;
        }
        else {
            return 0;
        }
    }
}