// 3DApp.cpp
// KlayGE 3DApp类 实现文件
// Ver 2.0.0
// 版权所有(C) 龚敏敏, 2003
// Homepage: http://www.enginedev.com
//
// 2.0.0
// 初次建立 (2003.7.10)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#define NOMINMAX

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/ThrowErr.hpp>
#include <KlayGE/SharedPtr.hpp>
#include <KlayGE/Memory.hpp>
#include <KlayGE/Math.hpp>
#include <KlayGE/Engine.hpp>
#include <KlayGE/RenderWindow.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/RenderFactory.hpp>

#include <cassert>
#include <windows.h>

#include <KlayGE/App3D.hpp>

namespace KlayGE
{
	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	App3DFramework::App3DFramework()
	{
		Engine::AppInstance(*this);
	}

	App3DFramework::~App3DFramework()
	{
		this->DelObjects();
	}

	// 建立应用程序窗口和D3D接口
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::Create(const String& name, const RenderSettings& settings)
	{
		Engine::RenderFactoryInstance().RenderEngineInstance().CreateRenderWindow(name, settings);

		this->InitObjects();
	}

	void App3DFramework::Run()
	{
		Engine::RenderFactoryInstance().RenderEngineInstance().StartRendering();

		this->DelObjects();
	}

	// 设置观察矩阵
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::LookAt(const Vector3& vEye, const Vector3& vLookAt,
												const Vector3& vUp)
	{
		RenderEngine& RenderEngine(Engine::RenderFactoryInstance().RenderEngineInstance());
		RenderTarget& activeRenderTarget(*(*RenderEngine.ActiveRenderTarget()));

		activeRenderTarget.GetViewport().camera.ViewParams(vEye, vLookAt, vUp);
		RenderEngine.ViewMatrix(activeRenderTarget.GetViewport().camera.ViewMatrix());
	}

	// 设置投射矩阵
	/////////////////////////////////////////////////////////////////////////////////
	void App3DFramework::Proj(float nearPlane, float farPlane)
	{
		assert(nearPlane != 0);
		assert(farPlane != 0);
		assert(farPlane > nearPlane);

		RenderEngine& renderEngine(Engine::RenderFactoryInstance().RenderEngineInstance());
		RenderTarget& activeRenderTarget(*(*renderEngine.ActiveRenderTarget()));
		Camera& camera(activeRenderTarget.GetViewport().camera);

		camera.ProjParams(PI / 4, static_cast<float>(activeRenderTarget.Width()) / activeRenderTarget.Height(),
			nearPlane, farPlane);
		renderEngine.ProjectionMatrix(camera.ProjMatrix());
	}
}