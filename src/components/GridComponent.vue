<template>
  <div class="container">
    <div class="webcam">
      <video ref="webcam" autoplay playsinline></video>
    </div>
    <div class="grid">
      <div v-for="row in 4" :key="row" class="row">
        <div
          v-for="col in 5"
          :key="`${row}-${col}`"
          :class="['square', { 'lit-up': isLitUp(`${row}-${col}`) }]"
          @click="lightUpSquare(`${row}-${col}`)"
        ></div>
      </div>
    </div>
  </div>
</template>

<script>
import { db, set, ref } from '@/components/firebase';

export default {
  data() {
    return {
      litSquares: {},
    };
  },
  mounted() {
    this.initWebcam();
  },
  methods: {
    lightUpSquare(squareId) {
      this.$set(this.litSquares, squareId, true);
      const [row, col] = squareId.split('-').map(Number);
      const totalRows = 3;
      const adjustedRow = totalRows + 2 - row;
      set(ref(db, 'clickedSquares'), { X: col, Y: adjustedRow });
      setTimeout(() => {
        this.$delete(this.litSquares, squareId);
      }, 1000);
    },
    isLitUp(squareId) {
      return !!this.litSquares[squareId];
    },
    initWebcam() {
      if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
        navigator.mediaDevices.getUserMedia({ video: true })
          .then((stream) => {
            this.$refs.webcam.srcObject = stream;
          })
          .catch((error) => {
            console.error("Webcam not accessible:", error);
          });
      }
    },
  },
};
</script>

<style>
.container {
  display: flex;
  flex-direction: column;
  align-items: center;
}
.webcam {
  margin-bottom: 20px;
}
.grid {
  display: flex;
  flex-direction: column;
  user-select: none;
}
.row {
  display: flex;
}
.square {
  width: 70px;
  height: 70px;
  border: 1px solid #ffffff;
  margin: -1px;
  cursor: pointer;
  background-color: #000;
  transition: background-color 1s ease-out;
}
.lit-up {
  background-color: #fff;
  animation: fadeAway 1s ease-out forwards;
}
@keyframes fadeAway {
  from {
    background-color: #fff;
  }
  to {
    background-color: #000;
  }
}
</style>
