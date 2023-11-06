#include "Engine.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Engine* engine = new Engine;
	engine->Initialize();
	engine->Update();
	engine->Finalize();
	delete engine;
	return 0;
}