#include "MainComponent.h"

#include <cstdio>
#include <cmath>

//==============================================================================
MainComponent::MainComponent()
{
	mouseState.resize(2);
	mouseState[1].type = "Pen";
	setSize(1600, 900);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	auto area = getLocalBounds().toDouble();
	
	for (auto& ms : mouseState)
	{
		if (ms.active) {
			auto x = static_cast<int>(std::round(ms.posX * area.getWidth()));
			auto y = static_cast<int>(std::round(ms.posY * area.getHeight()));

			g.setColour(ms.colour);
			g.fillEllipse(x - 25, y - 25, 50, 50);

			g.drawSingleLineText(ms.type + " #" + std::to_string(ms.index + 1), x, y - 40);
		}
	}
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
	auto area = getLocalBounds().toDouble();
	int idx = 0;
	switch (event.source.getType()) {
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = 2 + event.source.getIndex();
		if (idx >= mouseState.size()) {
			mouseState.resize(idx + 1);
			mouseState[idx].type = "Touch";
			mouseState[idx].index = event.source.getIndex();
			mouseState[idx].colour = juce::Colour::fromFloatRGBA(randomGen.nextFloat(), randomGen.nextFloat(), randomGen.nextFloat(), 1.0);
		}
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}


	mouseState[idx].active = true;
	mouseState[idx].posX = static_cast<double>(event.x) / area.getWidth();
	mouseState[idx].posY = static_cast<double>(event.y) / area.getHeight();
	repaint();
}

void MainComponent::mouseUp(const juce::MouseEvent& event)
{
	int idx = 0;
	switch (event.source.getType()) {
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = 2 + event.source.getIndex();
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}

	mouseState[idx].active = false;
	repaint();
}

void MainComponent::mouseDrag(const juce::MouseEvent& event)
{
	auto area = getLocalBounds().toDouble();
	int idx = 0;
	switch (event.source.getType()) {
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = 2 + event.source.getIndex();
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}


	mouseState[idx].posX = static_cast<double>(event.x) / area.getWidth();
	mouseState[idx].posY = static_cast<double>(event.y) / area.getHeight();
	repaint();
}