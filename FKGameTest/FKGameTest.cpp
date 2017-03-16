/**
*	created:		2013-4-13   0:55
*	filename: 		FKGameTest
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/FK2DEngine2.h"
#include "../FK2DEngine2/Include/UI/UnitTest/FKUnitTest.h"
//------------------------------------------------------------------------
#pragma warning( disable:4244 )
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::core;
using namespace FK2DEngine2::video;
using namespace FK2DEngine2::input;
using namespace FK2DEngine2::system;
using namespace FK2DEngine2::audio;
using namespace FK2DEngine2::math;
using namespace FK2DEngine2::scene::S2D;
using namespace FK2DEngine2::scene::S3D;
using namespace FK2DEngine2::actor;
//------------------------------------------------------------------------
IVideoDriver *					videoDriver;
ITexture *						texture;
ITexture *						texture2;
IInputDriver *					inputDriver;
IAudioDriver *					audioDriver;
IEngine *						engine;
ISound *						sound;
I2DSceneManager *				i2DSceneManager;
S2DQuad							renderObject;
IFont *							font;
IRenderObjectSceneNode *		node1;
ILightSceneNode *				light1;
ICameraSceneNode *				camera1;
I3DSceneManager *				c3dmanager;
UnitTest*						pUnit;
wchar_t							szInfoBuf[2048];
CFKTrace*						trace;
//------------------------------------------------------------------------
struct Pos
{
	int x;
	int y;
}pos;
//------------------------------------------------------------------------
bool MyUpateTest()
{
	static float rotate = 0.0f;
	// 开始渲染
	videoDriver->beginScene(SColor::cyan(),E_CLEAR_COLOR|E_CLEAR_ZBUFFER);
	{
		// 每帧刷新Input设备状态【使用DInput只能获取两帧间偏移】
		inputDriver->refreshDriverState();

		// 使用UIInput获取鼠标当前绝对位置【使用WINDOWS消息只能获取绝对位置】
		engine->getUIInput()->GetMousePos(pos.x, pos.y);

		//Vector3 mouseMove = inputDriver->getMouse()->getMouseRelativePos();
		//	pos.x += (int)(mouseMove.x);
		//	pos.y += (int)(mouseMove.y);

		// 模拟消息处理
		if (inputDriver->getMouse()->getMouseButtonState(E_MOUSE_BUTTON_MIDDLE,E_BUTTON_DOWN))
			pos.x += 100;

		// 绘制纹理【不推荐使用，使用UI比较好】
		videoDriver->drawText(font,740,745,SColor::red(),"Hello world【中文支持】");
		
		// 立方体旋转
		node1->setRotate(Vector3(rotate,rotate,rotate));

		// 渲染2D对象
		i2DSceneManager->begin2DScene();
		i2DSceneManager->RenderQuad(renderObject,pos.x - 60, pos.y - 60,	127);
		i2DSceneManager->RenderQuad(renderObject,pos.x, pos.y - 60,			128);
		i2DSceneManager->RenderQuad(renderObject,pos.x - 60, pos.y,			190);
		i2DSceneManager->drawAll( engine->getUICanvas() );
		i2DSceneManager->end2DScene();

		// 渲染3D场景
		c3dmanager->begin3DScene();
		c3dmanager->drawAll();
		c3dmanager->end3Dscene();

		i2DSceneManager->renderUI( engine->getUICanvas() );
	}
	// 关闭渲染
	videoDriver->endScene();

	rotate += 0.01f;
	return true;
}
//------------------------------------------------------------------------
void SetBaseProperty()
{
	engine->setEngineStateStr(E_ENGINE_STATE_WINDOWNAME,L"FK测试窗口");
	engine->setEngineStateI(E_ENGINE_STATE_WINDOWWIDTH, 1024);
	engine->setEngineStateI(E_ENGINE_STATE_WINDOWHEIGHT,768);
	engine->setEngineStateF(E_ENGINE_STATE_FPS,60.0);
}
//------------------------------------------------------------------------
void Init2DAndSound()
{
	// 测试音乐
	sound = audioDriver->loadSound(L"测试音乐",L"测试.mp3",E_SOUND_TYPE_STREAM);
	IChannel * c = audioDriver->playSound(sound);

	// 测试纹理
	renderObject.makeRect(58,58);
	texture2 = videoDriver->loadTexture(L"测试平面纹理",L"bb.jpg");
	renderObject.texture = texture2;
	pos.x = 0; 
	pos.y = 0;

	// 测试字体
	font = videoDriver->loadFont(L"测试字体",24,12,300,L"Times New Roman");

	// 自己的UI初始化
	pUnit = new UnitTest( engine->getUICanvas() );
	pUnit->SetPos( 0, 0 );

	//CActor* m_pBackgroud = new CActor();
	//m_pBackgroud->SetLayer( 233 );
	//m_pBackgroud->SetSize( 1024, 768 );
	//m_pBackgroud->SetSprite( L".\\Res\\LoginBK.jpg" );
}
//------------------------------------------------------------------------
void MyShut()
{

}
//------------------------------------------------------------------------
int main ()
{
	// 不能启动超过二个相同的进程
	if(!FKProcessLimitGuard<1>::Instance()->IsOwned())
	{
		MessageBox(0, L"对不起，本游戏不支持双开以及多开。", L"FreeKnightGame提示", 0);
		return 0;
	}

	// 初始化引擎对象
	engine = GetEngine();
	SetBaseProperty();
	engine->initEngine();

	videoDriver = 		engine->getVideoDriver();
	inputDriver = 		engine->getInputDriver();
	audioDriver = 		engine->getAudioDriver();
	i2DSceneManager =	engine->get2DSceneManager();
	c3dmanager =		engine->get3DSceneManager();
	trace	=			engine->getTraceWin();

	trace->ThreadSafeDebugPrintLnWithTime(L"Init engine over.");
	trace->ThreadSafeDebugPrintLn(L"Create demo light.");

	SLight light;
	light.diffuse = SColor::white();
	light.type = E_LIGHT_TYPE_POINT;
	light.specular = SColor::yellow();

	trace->ThreadSafeDebugPrintLn(L"Init other info.");

	Init2DAndSound();

	((FK2DEngine2::scene::S2D::C2DSceneManager*)i2DSceneManager)->Add(new FK2DEngine2::actor::CGridActor());
	
	trace->ThreadSafeDebugPrintLn(L"Create base camere, cube, and add them to scene.");

	node1 = c3dmanager->addCubeSceneNode(L"测试立方体",NULL,Vector3(0,0,0),Vector3(1,1,1));
	texture = videoDriver->loadTexture(L"测试立方体纹理",L"aa.jpg");
	node1->setTexture( texture );
	node1->setMaterial(SMaterial::greenMaterial());
    light1 = c3dmanager->addLightSceneNode(L"测试灯光",NULL,Vector3(0.0,0.0,-3.0),light);
	camera1 = c3dmanager->addCameraSceneNode(L"测试摄像机",NULL,Vector3(0,0,-4),Vector3(0,0,4),Vector3(0,1,0));

	trace->ThreadSafeDebugPrintLn(L"Be ready to enter main loop.");
	// 主循环
	while (engine->runEngine())
	{
		// 自己的每帧循环
		if (!MyUpateTest())
		{
			break;
		}
	}
	trace->ThreadSafeDebugPrintLn(L"Quit main loop.");

	MyShut();

	trace->ThreadSafeDebugPrintLn(L"Free all resource.");

	// 关闭引擎，引擎管理对象全部释放
	engine->shutEngine();
	return 0;
}
//------------------------------------------------------------------------