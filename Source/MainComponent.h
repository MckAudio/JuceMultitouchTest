#pragma once

#include <JuceHeader.h>
#include <vector>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    struct MouseState {
        bool active{ false };
        int index{ 0 };
        Point<int> start{ 0, 0 };
        double pressure { 0.0 };
        std::string type{ "Mouse" };
        juce::Colour colour{juce::Colours::orange};
        std::vector<Point<int>> path;
    };

    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseDown(const juce::MouseEvent &event) override;
    void mouseUp(const juce::MouseEvent &event) override;
    void mouseDrag(const juce::MouseEvent &event) override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    bool mouseActive{false};
    int posX{0};
    int posY{0};

    std::vector<MouseState> mouseState;

    juce::Random randomGen;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
