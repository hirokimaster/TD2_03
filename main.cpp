#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Engine.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#ifdef _DEBUG
	// リークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
	std::unique_ptr<Engine> engine;
	engine = std::make_unique<Engine>();
	engine->Initialize();
	engine->Run();
	engine->Finalize();
#ifdef _DEBUG
	// リークチェック
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;
}