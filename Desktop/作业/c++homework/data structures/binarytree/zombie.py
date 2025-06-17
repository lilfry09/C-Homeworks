class Zombie:
    def __init__(self, health, speed, damage):
        self.health = health
        self.speed = speed
        self.damage = damage
    
    def move(self):
        print(f"僵尸以速度{self.speed}移动,当前血量：{self.health}")

    def attack(self, target):
        target.health -= self.damage
        print("僵尸攻击目标，造成{self.damage}点伤害，"
        "目标剩余血量：{target.health}")
    
    def is_alive(self):
        return self.health > 0
    
    def beattack(self, plant_damage):
        self.health -= plant_damage
        if self.health <= 0:
            print("僵尸被植物攻击，死亡")
        else:
            print("僵尸被植物攻击，剩余血量：{self.health}")

class BucketZombie(Zombie):
    def __init__(self, health):
        super().__init__(health, speed)
        self.buckethealth = 100
    
    def bucketbeattack(self, plant_damage):
        self.buckethealth -= plant_damage
        if self.buckethealth <= 0:
            print("铁桶被击破")
            super().beattack(30)
        else:
            print("铁桶剩余血量：{self.buckethealth}")
                  
class Plant:
    def __init__(self, health, speed, damage):
        self.health = health
        self.speed = speed
        self.damage = damage

    def attack(self, target):
        target.health -= self.damage

if __name__ == "__main__":
    zombie = Zombie(100, 5, 10)
    zombie.move()
    zombie.attack(50)

    # 创建铁桶僵尸
    bucket_zombie = BucketZombie(health=150, speed=3, damage=15)
    bucket_zombie.move()
    bucket_zombie.bucket_be_attacked(50)  # 第一次攻击铁桶
    bucket_zombie.bucket_be_attacked(60)  # 第二次击破铁桶并伤到本体
    
    # 创建植物
    pea_shooter = Plant(health=50, damage=25)
    pea_shooter.attack(bucket_zombie)  # 豌豆射手攻击铁桶僵尸



