/*
  ==============================================================================

    CartoonRotarySlider.h
    Created: 30 Dec 2024 7:49:15am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CartoonRotarySlider : public juce::Slider
{
public:
    CartoonRotarySlider() {
        setSliderStyle(juce::Slider::Rotary);
    }

    void mouseDown(const juce::MouseEvent& event) override
    {
        // Record the initial mouse position when the drag starts
        startDragY = event.position.y;
        startValue = getValue(); // Store the slider's value at the start of the drag
    }

    void mouseDrag(const juce::MouseEvent& event) override
    {
        // Calculate the vertical distance moved
        float distanceDragged = startDragY - event.position.y; // Negative for downward drag

        // Scale the vertical drag distance to a change in slider value
        float range = getMaximum() - getMinimum();
        float sensitivity = 0.0035f; // Adjust sensitivity as needed
        float newValue = startValue + distanceDragged * range * sensitivity;

        // Set the new slider value, clamping it to the slider's range
        setValue(juce::jlimit<double>(getMinimum(), getMaximum(), static_cast<double>(newValue)));
    }

private:
    float startDragY = 0.0f; // Starting Y-coordinate of the drag
    float startValue = 0.0f; // Starting value of the slider
};
