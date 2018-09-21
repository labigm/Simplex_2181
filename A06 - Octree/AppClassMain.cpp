#include "AppClass.h"
using namespace Simplex;
sf::Image LoadImageFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Image image;
	if (!image.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load image from memory.");

	return image;
}
Application::Application() {}
Application::Application(Application const& input) {}
Application& Application::operator=(Application const& input) { return *this; }
Application::~Application(void) 
{
	Release();
	
	//release controllers
	ReleaseControllers();

	// Release the Simplex singletons
	Simplex::ReleaseAllSingletons();
	SafeDelete(m_pWindow);
}
void Application::InitControllers(void)
{
	//Make sure this method is only executed once
	//else release the controllers first
	static bool bInit = false;
	if (bInit) ReleaseControllers();

	//Init all pointers
	for (uint i = 0; i < 8; ++i)
		m_pController[i] = new ControllerInput();

	m_uActCont = 0;
	m_uControllerCount = 0;
	for (uint i = 0; i < 8; ++i)
	{
		if (sf::Joystick::isConnected(i))
		{
			ProcessJoystickConnected(i);
		}
	}
	bInit = true;
}
void Application::ReleaseControllers(void)
{
	for (uint i = 0; i < 8; ++i)
	{
		if (m_pController[i] != nullptr)
		{
			delete m_pController[i];
			m_pController[i] = nullptr;
		}
	}
	m_uControllerCount = 0;
}
void Application::Run(void)
{
	//Initialize the system with default values it was not done in the Main.cpp
	Init();

	// run the main loop
	m_bRunning = true;
	sf::Vector2i pos = m_pWindow->getPosition();
	sf::Vector2u size = m_pWindow->getSize();
	while (m_bRunning)
	{
		// handle events
		sf::Event appEvent;
		while (m_pWindow->pollEvent(appEvent))
		{
			switch (appEvent.type)
			{
			case sf::Event::Closed:
				// end the program
				m_bRunning = false;
				break;
			case sf::Event::Resized:
				size = m_pWindow->getSize();
				m_pSystem->SetWindowWidth(size.x);
				m_pSystem->SetWindowHeight(size.y);
				Reshape();
				break;
			case sf::Event::MouseMoved:
				ProcessMouseMovement(appEvent);
				if (pos != m_pWindow->getPosition())
				{
					pos = m_pWindow->getPosition();
					size = m_pWindow->getSize();

					m_pSystem->SetWindowX(pos.x);
					m_pSystem->SetWindowY(pos.y);
					m_pSystem->SetWindowWidth(size.x);
					m_pSystem->SetWindowHeight(size.y);
				}
				break;
			case sf::Event::MouseButtonPressed:
				ProcessMousePressed(appEvent);
				break;
			case sf::Event::MouseButtonReleased:
				ProcessMouseReleased(appEvent);
				break;
			case sf::Event::MouseWheelScrolled:
				ProcessMouseScroll(appEvent);
				break;
			case sf::Event::KeyPressed:
				ProcessKeyPressed(appEvent);
				break;
			case sf::Event::KeyReleased:
				ProcessKeyReleased(appEvent);
				break;
			case sf::Event::TextEntered:
				if (appEvent.text.unicode > 0 && appEvent.text.unicode < 0x10000)
					ImGui::GetIO().AddInputCharacter(appEvent.text.unicode);
				break;
			case sf::Event::JoystickButtonPressed:
				ProcessJoystickPressed(appEvent);
				break;
			case sf::Event::JoystickButtonReleased:
				ProcessJoystickReleased(appEvent);
				break;
			case sf::Event::JoystickMoved:
				ProcessJoystickMoved(appEvent);
				break;
			case sf::Event::JoystickConnected:
				ProcessJoystickConnected(appEvent.joystickConnect.joystickId);
				break;
			case sf::Event::JoystickDisconnected:
				InitControllers();
				break;
			case sf::Event::GainedFocus:
				m_bFocused = true;
				break;
			case sf::Event::LostFocus:
				m_bFocused = false;
				break;
			}
		}
		ProcessKeyboard();//Continuous events
		ProcessJoystick();//Continuous events
		Update();
		Display();
	}

	//Write configuration of this program
	WriteConfig();
}
void Application::ClearScreen(vector4 a_v4ClearColor)
{
	if (a_v4ClearColor != vector4(-1.0f))
	{
		m_v4ClearColor = a_v4ClearColor;
	}
	glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
}
void Application::Reshape(void)
{
	sf::Vector2i pos = m_pWindow->getPosition();
	sf::Vector2u size = m_pWindow->getSize();

	m_pSystem->SetWindowX(pos.x);
	m_pSystem->SetWindowY(pos.y);
	m_pSystem->SetWindowWidth(size.x);
	m_pSystem->SetWindowHeight(size.y);

	// adjust the viewport when the window is resized
	glViewport(0, 0, size.x, size.y);
	m_pMeshMngr->SetRenderTarget(0, 0, 0, size.x, size.y);
}
void Application::Init(String a_sApplicationName, int a_uSize, bool a_bFullscreen, bool a_bBorderless)
{
	static bool bInitializated = false;
	if (bInitializated)
		return;

	//Init System
	m_pSystem = SystemSingleton::GetInstance();
	m_pSystem->SetWindowResolution(a_uSize);
	Init(a_sApplicationName, m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight(), a_bFullscreen, a_bBorderless);
	
	//Initializated flag
	bInitializated = true;
}
void Application::Init(String a_sApplicationName, uint a_uWidth, uint a_uHeight, bool a_bFullscreen, bool a_bBorderless)
{
	static bool bInitializated = false;
	if (bInitializated)
		return;

	m_bRunning = false;

	//Init System
	m_pSystem = SystemSingleton::GetInstance();

	if(a_sApplicationName == "")
		m_pSystem->SetWindowName(m_pSystem->GetAppName());
	else
		m_pSystem->SetWindowName(a_sApplicationName);
	m_pSystem->SetWindowWidth(a_uWidth);
	m_pSystem->SetWindowHeight(a_uHeight);
	m_pSystem->SetWindowFullscreen(a_bFullscreen);

	//Get light manager
	m_pLightMngr = LightManager::GetInstance();

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	m_v4ClearColor = vector4(C_BLUE_CORNFLOWER, 1.0f);
	
	//Read configuration
	ReadConfig(); // <<< the .ini file will have preference over programmer >>>

	//Init GLFW Window
	InitWindow(m_pSystem->GetWindowName());
		
	//Init Camera
	m_pCameraMngr = CameraManager::GetInstance();
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What I'm looking at
		AXIS_Y);//What is up
	
	//Init Mesh Manager
	m_pMeshMngr = MeshManager::GetInstance();

	//Init sizes
	Reshape();

	//Init GUI
	m_bGUI_Main = true;
	m_bGUI_Console = true;
	m_bGUI_Controller = false;
	m_bGUI_Test = false;
	InitIMGUI();

	//Init controllers
	InitControllers();

	//Init Entity Manager
	m_pEntityMngr = MyEntityManager::GetInstance();

	//Init variables
	InitVariables();

	//Initializated flag
	bInitializated = true;
}
void Application::InitWindow(String a_sWindowName)
{
	uint uStyle = sf::Style::Default;

	if (m_pSystem->IsWindowBorderless())
		uStyle = sf::Style::None;
	
	if (m_pSystem->IsWindowFullscreen())
		uStyle = sf::Style::Fullscreen;
		
	//If OpenGL 4.5 is not supported in the system glfw will warn you and determine the highest possible version
	m_pWindow = new sf::Window(	sf::VideoMode(m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight(), 32), //Window size
								a_sWindowName, //window name
								uStyle, //window style
								sf::ContextSettings(	24, //depth buffer
														0,	//stencil
														0,	//Antialiasing
														4,	//OpenGL Major
														5,	//OpenGL Minor
														0,	//Attributes
														false //sRGB
													)); //context settings
	m_pWindow->setVerticalSyncEnabled(true);
	m_pWindow->setFramerateLimit(m_pSystem->GetMaxFrameRate());
	sf::Image icon = LoadImageFromResource("iconPNG");
	m_pWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);
}
void Application::ReadConfig(void)
{
	String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
	String App = m_pSystem->GetAppName();
	App = sRoot + App + ".ini";

	FileReader reader;
	//If the file doesn't exist, exit this method
	if (reader.ReadFile(App.c_str()) == OUT_ERR_FILE_MISSING)
	{
		return;
	}

	//read the file for startup values
	reader.Rewind();
	while (reader.ReadNextLine() == OUT_RUNNING)
	{
		String sWord = reader.GetFirstWord();

		int nLenght = reader.m_sLine.length();
		char* zsTemp = new char[nLenght];

		if (sWord == "Fullscreen:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
			m_pSystem->SetWindowFullscreen(nValue != 0);
		}
		else if (sWord == "Borderless:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
			m_pSystem->SetWindowBorderless(nValue != 0);
		}
		else if (sWord == "FrameRate:")
		{
			int nValue;
			sscanf_s(reader.m_sLine.c_str(), "FrameRate: %d", &nValue);
			m_pSystem->SetMaxFrameRate(static_cast<uint>(nValue));
		}
		else if (sWord == "Resolution:")
		{
			int nValue1;
			int nValue2;
			sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1, &nValue2);
			m_pSystem->SetWindowWidth(nValue1);
			m_pSystem->SetWindowHeight(nValue2);
		}
		else if (sWord == "Ambient:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
			m_pLightMngr->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
		}
		else if (sWord == "Background:")
		{
			float fValueX;
			float fValueY;
			float fValueZ;
			float fValueW;
			sscanf_s(reader.m_sLine.c_str(), "Background: [%f,%f,%f,%f]", &fValueX, &fValueY, &fValueZ, &fValueW);
			m_v4ClearColor = vector4(fValueX, fValueY, fValueZ, fValueW);
		}
		else if (sWord == "AmbientPower:")
		{
			float fValue;
			sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
			m_pLightMngr->SetIntensity(fValue, 0);
		}
		else if (sWord == "Data:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderData(zsTemp);
		}
		else if (sWord == "BTO:")
		{
			sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMBTO(zsTemp);
		}
		else if (sWord == "FBX:")
		{
			sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMFBX(zsTemp);
		}
		else if (sWord == "OBJ:")
		{
			sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderMOBJ(zsTemp);
		}
		else if (sWord == "Level:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderLVL(zsTemp);
		}
		else if (sWord == "Textures:")
		{
			sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
			m_pSystem->m_pFolder->SetFolderTextures(zsTemp);
		}

		delete[] zsTemp;
		zsTemp = nullptr;
	}
	reader.CloseFile();
}
void Application::WriteConfig(void)
{
	// Write the configuration for this application
	String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
	String App = m_pSystem->GetAppName();
	App = sRoot + App + ".ini";

	FILE *pFile;
	fopen_s(&pFile, App.c_str(), "w");
	if (!pFile)	//If we couldn't create the file we exit without changes.
		return;

	//Save DEFAULT_V3NEG values for a config file
	rewind(pFile);
	fprintf(pFile, "# Configuration file for the program: %s", m_pSystem->GetAppName().c_str());

	fprintf(pFile, "\n\nFullscreen: ");
	if (m_pSystem->IsWindowFullscreen())
		fprintf(pFile, "1");
	else
		fprintf(pFile, "0");

	fprintf(pFile, "\nBorderless: ");
	if (m_pSystem->IsWindowBorderless())
		fprintf(pFile, "1");
	else
		fprintf(pFile, "0");

	fprintf(pFile, "\n\nFrameRate: ");
	fprintf(pFile, "%d", m_pSystem->GetMaxFrameRate());

	fprintf(pFile, "\n\nResolution: [ %d x %d ]", m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());
	fprintf(pFile, "\n# Resolution: [ 640 x 480 ]");
	fprintf(pFile, "\n# Resolution: [ 1280 x 720 ]");
	fprintf(pFile, "\n# Resolution: [ 1680 x 1050 ]");
	fprintf(pFile, "\n# Resolution: [ 1920 x 1080 ]");
	fprintf(pFile, "\n# Resolution: [ 2560 x 1080 ]");
	

	fprintf(pFile, "\n\nAmbient: [%.2f,%.2f,%.2f]",
		m_pLightMngr->GetColor(0).r, m_pLightMngr->GetColor(0).g, m_pLightMngr->GetColor(0).b);
	fprintf(pFile, "\nAmbientPower: %.2f", m_pLightMngr->GetIntensity(0));

	fprintf(pFile, "\n\nBackground: [%.3f,%.3f,%.3f,%.3f]",
		m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);

	fprintf(pFile, "\n\n# Folders:");
	fprintf(pFile, "\nData:		%s", m_pSystem->m_pFolder->GetFolderData().c_str());
	fprintf(pFile, "\nBTO:		%s", m_pSystem->m_pFolder->GetFolderMBTO().c_str());
	fprintf(pFile, "\nFBX:		%s", m_pSystem->m_pFolder->GetFolderMFBX().c_str());
	fprintf(pFile, "\nOBJ:		%s", m_pSystem->m_pFolder->GetFolderMOBJ().c_str());
	fprintf(pFile, "\nLevel:		%s", m_pSystem->m_pFolder->GetFolderLVL().c_str());
	fprintf(pFile, "\nTextures:	%s", m_pSystem->m_pFolder->GetFolderTextures().c_str());

	fclose(pFile);
}