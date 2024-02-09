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
    }, 300); // 500 milliseconds = 0.5 second
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
    }, 400); // 500 milliseconds = 0.5 second
  }).catch((error) => {
    console.error('Error performing action:', error);
  });
},

  },
};
</script>

<style scoped>
div {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 20px;
  padding: 20px;
  background-color: #121212; /* Dark background */
  color: #e0e0e0; /* Light text color for contrast */
}

button {
  background-color: #333;
  color: #fff;
  border: none;
  padding: 10px 20px;
  border-radius: 5px;
  cursor: pointer;
  transition: background-color 0.3s, transform 0.1s;
}

button:hover {
  background-color: #444;
}

button:active {
  background-color: #555;
  transform: scale(0.98); /* Subtle press effect */
}

p {
  font-size: 1.2rem;
}

/* Style adjustments for input and range if used later */
/* input[type="text"], input[type="range"] {
  padding: 10px;
  border-radius: 5px;
  border: 1px solid #333;
  background-color: #222;
  color: #fff;
  outline: none;
}

input[type="range"] {
  -webkit-appearance: none;
  width: 100%;
  background: #333;
}

input[type="range"]::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 20px;
  height: 20px;
  background: #777;
  cursor: pointer;
} */
</style>

