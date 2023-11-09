#include "Engine.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Engine* engine = new Engine;
	engine->Initialize();
	engine->Update();
	delete engine;
	engine->Finalize();
	return 0;
}