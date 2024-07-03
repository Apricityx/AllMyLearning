import { createSSRApp } from "vue";
import App from "./App.vue";
import 'vuetify/styles'
import {createVuetify} from 'vuetify'
import * as components from 'vuetify/components'
import * as directives from 'vuetify/directives'
import uviewPlus from 'uview-plus'
export function createApp() {
  const app = createSSRApp(App);
  const vuetify = createVuetify({
    ssr: true,
    components,
    directives,
  })
  app.use(vuetify);
  app.use(uviewPlus)
  return {
    app,
  };
}
