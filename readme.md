# Tank Battle

> <strong><big><green>This is a class work for C++ course of NEU.<green></big></strong>


## Design
#### 视角
游戏画面采用镜头(camera)跟随坦克的上帝视角，鼠标辅助炮塔旋转。
#### 坐标系
游戏整体有两套坐标系，一套是地图坐标系，以地图的左上角为坐标原点，向右为x轴正向，向下为y轴正向。
另外一套坐标系是镜头坐标系，以屏幕左上角为坐标原点，向右为x轴正向，向下为y轴正向。
#### 移动
坦克w/s键前进/后退，体现为地图相对于镜头的移动，坦克保持与镜头的相对静止
#### 旋转
a/d键 顺时针/逆时针旋转，统一采用x*PI的double类型。
