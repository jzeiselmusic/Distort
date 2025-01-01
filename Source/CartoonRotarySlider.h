/*
  ==============================================================================

    CartoonRotarySlider.h
    Created: 30 Dec 2024 7:49:15am
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CartoonLookAndFeel.h"

class CartoonRotarySlider : public juce::Slider
{
public:
    CartoonRotarySlider() {
        setSliderStyle(juce::Slider::Rotary);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        setLookAndFeel(&rotarySliderLookAndFeel);
        
        // Initialize the label
        valueLabel.setFont(juce::Font(16.0f, juce::Font::bold));
        valueLabel.setJustificationType(juce::Justification::centred);
        valueLabel.setColour(juce::Label::textColourId, juce::Colours::black);
        valueLabel.setInterceptsMouseClicks(false, false); // Don't block mouse events
        addAndMakeVisible(valueLabel);
        updateLabel();
        valueLabel.setVisible(false); // Hidden by default
    }

    void mouseDown(const juce::MouseEvent& event) override {
        updateLabel();
        valueLabel.setVisible(true);
        // Record the initial mouse position when the drag starts
        startDragY = event.position.y;
        startValue = getValue(); // Store the slider's value at the start of the drag
    
    }
    
    void valueChanged(void) override {
        updateLabel();
    }
    
    void mouseUp(const juce::MouseEvent& event) override {
        valueLabel.setVisible(false);
    }

    void mouseDrag(const juce::MouseEvent& event) override {
        // Calculate the vertical distance moved
        float startValueLog = juce::Decibels::gainToDecibels(startValue);
        float maxValueLog = juce::Decibels::gainToDecibels(getMaximum());
        float minValueLog = juce::Decibels::gainToDecibels(getMinimum());
        float distanceDragged = startDragY - event.position.y; // Negative for downward drag

        // Scale the vertical drag distance to a change in slider value
        float rangeLog = maxValueLog - minValueLog;
        float sensitivity = 0.003f; // Adjust sensitivity as needed
        float newValueLog = startValueLog + distanceDragged * sensitivity * rangeLog;
        float newValueGain = juce::Decibels::decibelsToGain(newValueLog);

        // Set the new slider value, clamping it to the slider's range
        setValue(juce::jlimit<double>(getMinimum(), getMaximum(), static_cast<double>(newValueGain)));
    }

private:
    float startDragY = 0.0f; // Starting Y-coordinate of the drag
    float startValue = 0.0f; // Starting value of the slider
    
    CartoonLookAndFeel rotarySliderLookAndFeel;
    
    juce::Label valueLabel;
    
    void updateLabel() {
        auto bounds = getLocalBounds();
        auto center = bounds.getCentre();
        valueLabel.setBounds(center.x - valueLabel.getWidth() / 2, center.y + 50, 65, 25); // Adjust dynamically
        valueLabel.setText(juce::String(getValue(), 3), juce::dontSendNotification);
    }
};
