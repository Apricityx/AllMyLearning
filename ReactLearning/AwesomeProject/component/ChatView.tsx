import React, {useState} from 'react';
import {StyleSheet, Image, Text, TextInput, View, Button, ScrollView} from 'react-native';

type ChatMessage = {};
const styles = StyleSheet.create({ //约定俗成的写法

})
const ChatView = (props: ChatMessage) => {
    return (
        <View>
            <ScrollView>
                <View>
                    <Text>ChatView</Text>
                </View>
            </ScrollView>
        </View>
    )
}
export default ChatView