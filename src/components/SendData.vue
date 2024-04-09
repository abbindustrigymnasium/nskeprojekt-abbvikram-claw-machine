<template>
  <div>
    <!-- Video Element to Display Webcam Feed -->
    <video id="webcam" autoplay playsinline ref="webcam"></video>

    <!-- Buttons for existing functionality -->
    <button @mousedown="startAdding" @mouseup="stopAdding">Hold to Add 1</button>
    <button @mousedown="startSubtracting" @mouseup="stopSubtracting">Hold to Subtract 1</button>
    <button @mousedown="setMotorData(1)" @mouseup="stopSettingMotorData">Hold for Motor/Data 1</button>
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
      stream: null, // for storing the media stream
    };
  },
  mounted() {
    this.initWebcam();
  },
  methods: {
    startAdding() {
      this.addingInterval = setInterval(() => {
        this.counter = Math.min(180, this.counter + 1);
        set(ref(db, 'servo'), {
          data: this.counter,
          slider: parseInt(this.slider),
        });
      }, 5);
    },
    stopAdding() {
      clearInterval(this.addingInterval);
      this.addingInterval = null;
    },
    startSubtracting() {
      this.subtractingInterval = setInterval(() => {
        this.counter = Math.max(-180, this.counter - 1);
        set(ref(db, 'servo'), {
          data: this.counter,
          slider: parseInt(this.slider),
        });
      }, 5);
    },
    stopSubtracting() {
      clearInterval(this.subtractingInterval);
      this.subtractingInterval = null;
    },
    setMotorData(value) {
      this.settingMotorDataInterval = setInterval(() => {
        set(ref(db, 'motor'), {
          data: value,
        });
      }, 5);
    },
    stopSettingMotorData() {
      clearInterval(this.settingMotorDataInterval);
      this.settingMotorDataInterval = null;
      set(ref(db, 'motor'), {
        data: 0,
      });
    },
    async initWebcam() {
      try {
        const constraints = { video: true, audio: false }; // Disable audio
        this.stream = await navigator.mediaDevices.getUserMedia(constraints);
        this.$refs.webcam.srcObject = this.stream;
      } catch (error) {
        console.error('Error accessing the webcam:', error);
      }
    },
    closeClaw() {
      set(ref(db, 'servo/claw'), 1).then(() => {
        console.log('Closing claw...');
        setTimeout(() => {
          set(ref(db, 'servo/claw'), 0).then(() => {
            console.log('Claw action completed.');
          });
        }, 300);
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
        }, 400);
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

button, video {
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

p, video {
  font-size: 1.2rem;
}

video {
  max-width: 100%;
  border: 2px solid #fff; /* White border for visibility */
}
</style>
