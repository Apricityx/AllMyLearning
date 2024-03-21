import React, {useState} from 'react';
import {StyleSheet, Image, Text, TextInput, View, Button, ScrollView} from 'react-native';

type ChatMessage = {};
const styles = StyleSheet.create({ //约定俗成的写法

})
const TextBar = (props: ChatMessage) => {
    return (
        <View>
            <TextInput style={{
                height: 100,
                borderColor: 'gray',
                borderWidth: 1
            }} //这里高度的单位是什么? //单位是像素 如果想要适配不同的屏幕，可以使用百分比 具体写法是：height: '10%'
                       placeholder="HELLO WORLD!"
                       onChangeText={(text) => console.log(text)}
            />
            <Button //这里不能用style属性，因为Button组件没有style属性
                title="Send"
                onPress={() => console.log('Send')}
            />
        </View>

    )
}
export default TextBar