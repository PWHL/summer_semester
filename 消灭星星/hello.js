var dom = document.getElementById("view");//视图,把id为view的值赋给dom
var ctx = dom.getContext("2d");//指定二维绘图 getContext() 方法返回一个用于在画布上绘图的环境。

var width=ctx.canvas.width;//边界宽度
var height=ctx.canvas.height;//边界高度

var tetris_width=width*0.95/10;//方块边长
var margin_width=width*0.05/11;//方块之间的距离

var pass=1;
var score=0;
var goalscore=1000;
var global;
var count=[];//存储颜色相同的方块
var Star=new Array();
function begin()
{                          //初始化数组，（当开始游戏或开始下一关时）
	for ( var i = 0; i < 10; i++)
	 {        //0~4为不同星星方块状态。 
		Star[i]=new Array();
		for ( var j = 0; j < 10; j++)
		 {
			var temp=Math.round(Math.random()*4+1);
			Star[i][j]=temp;
		}	
	}
}

function drawRect()
{                   //绘制背景和各个方块
	ctx.fillStyle="#c3e7fa";//边框颜色
	ctx.fillRect(0,0,width,height);
	var x=0;
	var y=0;
	for ( var i = 0; i < 10; i++) 
	{
		for ( var j = 0; j < 10; j++) 
		{
			if (Star[i][j]!=0)
			 {
				if (Star[i][j]==1)
				{
					ctx.fillStyle="red";
				}
				if (Star[i][j]==2) 
				{
					ctx.fillStyle="blue";
				}
				if (Star[i][j]==3) 
				{
					ctx.fillStyle="green";
				}
				if (Star[i][j]==4) 
				{
					ctx.fillStyle="yellow";
				}
				if (Star[i][j]==5) 
				{
					ctx.fillStyle="pink";
				}
				x=margin_width+i*(tetris_width+margin_width);
				y=margin_width+j*(tetris_width+margin_width);
				ctx.fillRect(x,y,tetris_width,tetris_width);
				drawStar(x+tetris_width/2,y+tetris_width/2,tetris_width*0.25,tetris_width*0.5);
			}		
		}	
	}
}
function drawStar(X,Y,r1,r2)
{     //在方块中画出星星图案
	ctx.save();//保存当前图像的一份拷贝
	var arr=[];
	for ( var i = 0; i < 10; i++)
	 {
		var s={};  
		//五角星的10个顶点分布在内切圆和外接圆上
		//Math.sin(x) Math.cos(x) 中x为弧度
		if (i%2==0)
		 {                                         
			s.x=r1*Math.cos(i*36*Math.PI/180);               
			s.y=r1*Math.sin(i*36*Math.PI/180);             
		 }
		else
		{
			s.x=r2*Math.cos(i*36*Math.PI/180);
			s.y=r2*Math.sin(i*36*Math.PI/180);
		}
		arr.push(s);
	}
	ctx.beginPath();
	ctx.translate(X,Y);//在一个位置画完图形后，在新的位置继续画
	ctx.rotate(270*Math.PI/180);
	ctx.moveTo(arr[0].x,arr[0].y);
	for ( var i = 1; i < 10; i++)
	 {
		ctx.lineTo(arr[i].x,arr[i].y);
	 }
	ctx.closePath();	
	ctx.stroke();//绘制当前路径的边框
	ctx.restore();//将绘图的状态保存
}


//判断某一列是否为空
function isEmpty(x)
{
	var i;
	var flag=false;
	for(i=0;i<10;i++)
	{
		if(Star[x][i]==0)
	 {
		flag=true;
	 }
	 else
	 {
		 flag=false;
	 }
	}
		return flag;
}
//判断是否能够往左移
function moveLeft()
{
	var flag=false;
	for(var i=0;i<9;i++)
	{
		if(isEmpty(i)&&!isEmpty(i+1))
		{
			flag=true;
		}
	}
	return flag;
}
//将数组往左移
function arrayMoveLeft()
{
		for(var i=0;i<9;i++)
		{
			if(isEmpty(i)&&!isEmpty(i+1))
			{
			for(var j=0;j<10;j++)
			{
				
					Star[i][j]=Star[i+1][j];
				    Star[i+1][j]=0;
				
			}
		}
		}
	if(moveLeft())
	{
		arrayMoveLeft();
	}
}
//判断是否能够往下移动
function moveDown()
{
	var i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<9;j++)
		{
			if(Star[i][j]!=0&&Star[i][j+1]==0)
			{
				return true;
			}
			
		}
	}
	return false;
}
//将数组往下移动
function arrayMoveDown()
{
	
	for(var i=0;i<10;i++)
	{
		for(var j=8;j>=0;j--)
		{
			if(Star[i][j]!=0&&Star[i][j+1]==0)
			{
			Star[i][j+1]=Star[i][j];
			Star[i][j]=0;
			}
		}
	}
	if(moveDown())
	{
		arrayMoveDown();
	}
}
//判断周围是否有相同颜色的方块
function isSame(x,y)
{
	if(Star[x][y]!=0)
	{
			if (x+1<=9&&Star[x+1][y]==Star[x][y]||
				x-1>=0&&Star[x-1][y]==Star[x][y]||
				y+1<=9&&Star[x][y+1]==Star[x][y]||
				y-1>=0&&Star[x][y-1]==Star[x][y]
			)
			 {
				return true;
			 }
	}
	return false;
}
//剩下方块的个数
function starNum()
{
	var i,j;
	var num=0;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(Star[i][j]!=0)
			{
				num=num+1;
			}
		}
	}
	return num;
}
//判断游戏结束
function checkGameOver()
{
	var flag=true;
	for(var i=0;i<10;i++)
	{
		for(var j=0;j<10;j++)
		{
			if(isSame(i,j))
			{
				flag=false;
			}
		}
	}
	
	return flag;
}

document.onclick = function()
{                     //鼠标点击时产生事件
 e=arguments[0]||window.event;//获取事件e
 x=e.clientX-(document.body.scrollWidth-width)/2;
//clientX：相对文档的水平座标
//document.body.scrollWidth网页可见区域宽
 y=e.clientY-150;
 for ( var i = 0; i <10; i++)
  {
	 for ( var j = 0; j < 10; j++)
	  {
		 if (x>=margin_width+i*(margin_width+tetris_width)&&                  //根据点击坐标寻找对应方块
					x<=(i+1)*(margin_width+tetris_width)&&
					y>=margin_width+j*(margin_width+tetris_width)&&
					y<=(j+1)*(margin_width+tetris_width)&&
					isSame(i,j)
				) 
				{	
					global=Star[i][j];
					var p={};//定义一个对象p
					p.x=i;
					p.y=j;
					count.push(p);   //push() 方法可向数组的末尾添加一个或多个元素，并返回新的长度。           //将点击到的方块的坐标放到数组count中，
					next(i,j);                  //找出与点击方块相邻的同样图案的方块
				}
	}	
}
 for ( var i = 0; i < count.length; i++)
  {       //将点击到的图案以及相邻同样图案清除
     Star[count[i].x][count[i].y]=0;
}
 drawRect();            
 score=score+count.length*10;           
 arrayMoveDown();
 arrayMoveLeft();
 count=[];
 window.setTimeout(function(){ctx.clearRect(0,0,width,height);drawRect();}, 200);

if (checkGameOver()) 
{
	var num=starNum();
	if (num>10) 
	{
		num=0;
	}
	if(num!=0)
	{
	score=score+num*20;
	}
	score=score+100;
	if(score<goalscore)
	       {
			 //document.write("<h1>游戏结束</h1>");
			document.write("<span style='white-space:pre;'> </span>");
			 document.write("<h1 align='center'style='color:red';>游戏结束</h1>");
			// document.write("font style='color:#FF0000;font-size:20px'>游戏结束</font>")
		     document.body.style.backgroundColor="#c3e7fa";
			 
	       }
	
	//score=score;
	pass+=1;
	goalscore=goalscore+1000;     
	begin();
	window.setTimeout(function(){ctx.clearRect(0,0,width,height);drawRect();}, 200);
}
document.getElementById("pass").innerHTML=pass;
document.getElementById("score").innerHTML=score;
document.getElementById("goalscore").innerHTML=goalscore;
};

//判断x,y在数组count中是否唯一
function checkone(ar,x,y)
{
	var flag=true;
	for(var i=0;i<ar.length;i++)
	{
		if(ar[i].x==x&&ar[i].y==y)
		{
			flag=false;
		}
	}
	return flag;
}
//找点X,Y附近相同颜色的星星
function next(x,y)
{
	if(x-1>=0)
	{
		if(Star[x-1][y]==global&&checkone(count,x-1,y))
		{
			var p={};
			p.x=x-1;
			p.y=y;
			count.push(p);
			next(x-1,y);
		}
	}
	if(x+1<=9)
	{
		if(Star[x+1][y]==global&&checkone(count,x+1,y))
		{
			var p={};
			p.x=x+1;
			p.y=y;
			count.push(p);
			next(x+1,y);
		}
	}
	if(y+1<=9)
	{
		if(Star[x][y+1]==global&&checkone(count,x,y+1))
		{
			var p={};
			p.x=x;
			p.y=y+1;
			count.push(p);
			next(x,y+1);
		}
	}
	if(y-1>=0)
	{
		if(Star[x][y-1]==global&&checkone(count,x,y-1))
		{
			var p={};
			p.x=x;
			p.y=y-1;
			count.push(p);
			next(x,y-1);
		}
	}
}
begin();
drawRect();
document.getElementById("pass").innerHTML=pass;
document.getElementById("score").innerHTML=score;
document.getElementById("goalscore").innerHTML=goalscore;


