#include "Engine.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<Engine> engine;
	engine = std::make_unique<Engine>();
	engine->Initialize();
	engine->Update();
	engine->Finalize();
	return 0;
}