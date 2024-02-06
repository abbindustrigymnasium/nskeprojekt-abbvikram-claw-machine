<template>
  <div>
    <!-- <label for="dataInput">Data:</label>
    <input v-model="data" type="text" id="dataInput" /> -->

    <!-- Slider -->
    <!-- <label for="slider">Slider Value: {{ slider }}</label> -->
    <!-- <input id="slider" type="range" v-model="slider" min="0" max="180" @input="updateSlider"> -->

    <!-- Button to continuously add 1 for every 5 milliseconds -->
    <button @mousedown="startAdding" @mouseup="stopAdding">Hold to Add 1</button>

    <!-- Button to continuously subtract 1 for every 5 milliseconds -->
    <button @mousedown="startSubtracting" @mouseup="stopSubtracting">Hold to Subtract 1</button>

    <!-- Button to set motor/data to 1 when held down -->
    <button @mousedown="setMotorData(1)" @mouseup="stopSettingMotorData">Hold for Motor/Data 1</button>

    <!-- Button to set motor/data to 2 when held down -->
    <button @mousedown="setMotorData(2)" @mouseup="stopSettingMotorData">Hold for Motor/Data 2</button>

   
    <button @click="closeClaw">Close Claw</button>

    <button @click="openClaw">Open Claw</button>


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
      settingMotorDataInterval: null,
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
    setMotorData(value) {
      // Set motor/data to the specified value when the button is pressed
      this.settingMotorDataInterval = setInterval(() => {
        set(ref(db, 'motor'), {
          data: value,
        });
      }, 5); // 5 milliseconds interval
    },
    stopSettingMotorData() {
      // Stop setting motor/data when the button is released
      clearInterval(this.settingMotorDataInterval);
      this.settingMotorDataInterval = null;

      // Set motor/data to 0
      set(ref(db, 'motor'), {
        data: 0,
      });
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
    closeClaw() {
  set(ref(db, 'servo/claw'), 1).then(() => {
    console.log('Closing claw...');
    setTimeout(() => {
      set(ref(db, 'servo/claw'), 0).then(() => {
        console.log('Claw action completed.');
      });
    }, 500); // 500 milliseconds = 0.5 second
  }).catch((error) => {
    console.error('Error performing action:', error);
  });
},

openClaw() {
  set(ref(db, 'servo/claw'), 2).then(() => {
    console.log('Opening claw...');
    setTimeout(() => {
      set(ref(db, 'servo/claw'), 0).then(() => {
        console.log('Claw action completed.');
      });
    }, 500); // 500 milliseconds = 0.5 second
  }).catch((error) => {
    console.error('Error performing action:', error);
  });
},

  },
};
</script>
