<template>
    <div>
      <label for="dataInput">Data:</label>
      <input v-model="data" type="text" id="dataInput" />
  
      <!-- Slider -->
      <label for="slider">Slider Value: {{ slider }}</label>
      <input id="slider" type="range" v-model="slider" min="0" max="180" @input="updateSlider">
  
      <!-- Button to continuously add 1 for every 5 milliseconds -->
      <button @mousedown="startAdding" @mouseup="stopAdding">Hold to Add 1</button>
  
      <!-- Button to continuously subtract 1 for every 5 milliseconds -->
      <button @mousedown="startSubtracting" @mouseup="stopSubtracting">Hold to Subtract 1</button>
  
      <!-- Display the counter value -->
      <p>Counter: {{ counter }}</p>
    </div>
  </template>
  
  <script>
  import { db, set, ref } from '@/components/firebase'; // Adjust the path accordingly
  
  export default {
    data() {
      return {
        data: '',
        slider: 0,
        addingInterval: null,
        subtractingInterval: null,
        counter: 0,
      };
    },
    methods: {
      startAdding() {
        // Start adding 1 for every 5 milliseconds when the button is pressed
        this.addingInterval = setInterval(() => {
          this.counter = Math.min(180, this.counter + 1);
  
          set(ref(db, 'servo'), {
            data: this.counter,
            slider: parseInt(this.slider),
          });
        }, 5); // 5 milliseconds interval
      },
      stopAdding() {
        // Stop adding when the button is released
        clearInterval(this.addingInterval);
        this.addingInterval = null;
      },
      startSubtracting() {
        // Start subtracting 1 for every 5 milliseconds when the button is pressed
        this.subtractingInterval = setInterval(() => {
          this.counter = Math.max(0, this.counter - 1);
  
          set(ref(db, 'servo'), {
            data: this.counter,
            slider: parseInt(this.slider),
          });
        }, 5); // 5 milliseconds interval
      },
      stopSubtracting() {
        // Stop subtracting when the button is released
        clearInterval(this.subtractingInterval);
        this.subtractingInterval = null;
      },
      updateSlider() {
        // Handle slider value changes
        console.log(`Updated Slider Value: ${this.slider}`);
  
        // Send the slider data to Firebase immediately
        set(ref(db, 'servo'), {
          data: this.data,
          slider: parseInt(this.slider),
        });
      },
    },
  };
  </script>
  