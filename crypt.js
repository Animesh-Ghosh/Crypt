var Module = {
  onRuntimeInitialized: function() {
    console.log('WASM module loaded!')
    console.log(Module)
    app.wasmModuleLoaded = true
  }
}

const app = new Vue({
  el: '#app',
  data: {
    selectedCipher: 'CaesarCipher',
    ciphers: [
      { id: 1, name: 'CaesarCipher' },
      { id: 2, name: 'CaesarCipherExt' },
      { id: 3, name: 'MonoAlpha' },
      { id: 4, name: 'RailFence' }
    ],
    message: '',
    caesarCipherExtKey: 3,
    wasmModuleLoaded: false,
    timeTaken: 0
  },
  methods: {
    getEncryptedMessage: function(selectedCipher, message, caesarCipherExtKey = 3) {
      let cipher = null
      const start = Date.now()
      switch(selectedCipher) {
      case 'CaesarCipher':
        cipher = new Module.CaesarCipher(message)
        break
      case 'CaesarCipherExt':
        cipher = new Module.CaesarCipherExt(message, caesarCipherExtKey)
        break
      case 'MonoAlpha':
        cipher = new Module.MonoAlpha(message)
        break
      case 'RailFence':
        cipher = new Module.RailFence(message)
        break
      }
      const encryptedMessage = cipher.Encrypt()
      const end = Date.now()
      const timeTaken = end - start
      cipher.delete()
      return { encryptedMessage, timeTaken }
    }
  },
  computed: {
    encryptedMessage: function() {
      let encryptedMessage = ''
      if (this.wasmModuleLoaded && this.message) {
        const enc = this.getEncryptedMessage(
          this.selectedCipher,
          this.message,
          this.caesarCipherExtKey
        )
        encryptedMessage = enc.encryptedMessage
        this.timeTaken = enc.timeTaken
      }
      return encryptedMessage
    },
    numberOfWords: function() {
      return this.message.length
    }
  }
})
