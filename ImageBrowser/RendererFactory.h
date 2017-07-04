#pragma once

#include "Renderer.h"
#include <memory>
#include <map>
#include <mutex>

enum class RenderType
{
	SDL_RENDERER,
	SDL_NONE
};

class RendererFactory
{

public:
	static RendererFactory& GetInstance() { return mInstance; }

	std::shared_ptr<IRenderer> CreateRenderer(RenderType renderType)
	{
		static std::mutex m;
		std::lock_guard<std::mutex> hold(m);
		auto sp = mRenderers[renderType].lock();		
		if (!sp) 
		{
			switch (renderType)
			{
			case RenderType::SDL_RENDERER:
				mRenderers[renderType] = sp = std::make_shared<Renderer>();
				break;
			case RenderType::SDL_NONE:
				break;
			default:
				break;
			}
		}

		return sp;
	}

private:
	std::map<RenderType, std::weak_ptr<IRenderer>> mRenderers;
	static RendererFactory mInstance;
};

RendererFactory RendererFactory::mInstance;