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
void MainComponent::paint(juce::Graphics &g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	auto area = getLocalBounds().toDouble();

	int size = 10;

	for (auto &ms : mouseState)
	{
		g.setColour(ms.colour);
		if (ms.active)
		{
			size = 10 + static_cast<int>(std::round(40.0 * ms.pressure));

			g.fillEllipse(ms.start.getX() - size / 2, ms.start.getY() - size / 2, size, size);

			g.drawSingleLineText(ms.type + " #" + std::to_string(ms.index + 1) + " (" + std::to_string(ms.pressure) + ")", ms.start.getX(), ms.start.getY() - size);
			
			Path p;
			p.startNewSubPath(ms.start.toFloat());
			for (size_t i = 1; i < ms.path.size(); i++)
			{
				p.lineTo(ms.path[i].toFloat());
			}
			g.strokePath(p, PathStrokeType(5.0f));
		}
	}
}

void MainComponent::resized()
{
	// This is called when the MainComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}

void MainComponent::mouseDown(const juce::MouseEvent &event)
{
	auto area = getLocalBounds().toDouble();
	size_t idx = 0;
	switch (event.source.getType())
	{
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = static_cast<size_t>(2 + event.source.getIndex());
		if (idx >= mouseState.size())
		{
			mouseState.resize(idx + 1);
			mouseState[idx].type = "Touch";
			mouseState[idx].index = event.source.getIndex();
		}
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}

	mouseState[idx].active = true;
	mouseState[idx].start = {event.x, event.y};
	mouseState[idx].path.clear();
	mouseState[idx].path.push_back(Point<int>(event.x, event.y));
	mouseState[idx].pressure = idx == 1 ? event.source.getCurrentPressure() : 1.0;
	mouseState[idx].colour = juce::Colour::fromFloatRGBA(randomGen.nextFloat(), randomGen.nextFloat(), randomGen.nextFloat(), 1.0);
	repaint();
}

void MainComponent::mouseUp(const juce::MouseEvent &event)
{
	size_t idx = 0;
	switch (event.source.getType())
	{
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = static_cast<size_t>(2 + event.source.getIndex());
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}

	mouseState[idx].active = false;
	mouseState[idx].pressure = idx == 1 ? event.source.getCurrentPressure() : 1.0;
	repaint();
}

void MainComponent::mouseDrag(const juce::MouseEvent &event)
{
	auto area = getLocalBounds().toDouble();
	size_t idx = 0;
	switch (event.source.getType())
	{
	case juce::MouseInputSource::mouse:
		idx = 0;
		break;
	case juce::MouseInputSource::touch:
		idx = static_cast<size_t>(2 + event.source.getIndex());
		break;
	case juce::MouseInputSource::pen:
		idx = 1;
		break;
	default:
		return;
	}

	mouseState[idx].path.push_back(Point<int>(event.x, event.y));
	mouseState[idx].pressure = idx == 1 ? event.source.getCurrentPressure() : 1.0;
	repaint();
}