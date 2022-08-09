// --- INICIALIZA TODAS AS VARIAVEIS GLOBAIS E O SERVIDOR
let leituraMao = [100, 100, 100, 100, 100]
let leituraMaoAnterior = [100, 100, 100, 100, 100]
let obj, mao;
let color = hexToRgb(document.getElementById('color').value)
let mov = [0.0, 0.0, 0.0, 0.0, 0.0]
let sentido = [1,1,1,1,1]

let socket = io.connect('http://localhost:4000');
socket.on('info', function(data) {
    leituraMao = [data.dedo1,data.dedo2,data.dedo3,data.dedo4,data.dedo5]
});

// --- INICIALIZA TODAS AS CARACTERISTICAS DA CENA E CHAMA O LOOP
const scene = setScene()
setLights()

const camera = setCamera(1)
const camera2 = setCamera(2)

const renderer = setRenderer()
const renderer2 = setRenderer()

setModel()
animate();

function animate() {
    requestAnimationFrame( animate );

    movDedos()
    movDedao()
    
    renderer.render( scene, camera );
    renderer2.render( scene, camera2 );
};

function setCamera(cam){
    const camera = new THREE.PerspectiveCamera( 75, window.innerWidth/2/ window.innerHeight, 0.1, 1000 );
    
    if(cam === 1){
        camera.position.z = 0;
        camera.position.y = 1;
        camera.position.x = -3;
        camera.rotation.y = -1.6;
        return camera
    }

    camera.position.z = 3;
    camera.position.y = 1;
    
    return camera
}

function setRenderer(){
    const renderer = new THREE.WebGLRenderer();
    renderer.setSize( window.innerWidth/2-20, window.innerHeight-20 );
    document.body.appendChild( renderer.domElement );
    return renderer;
}

function setScene(){
    const scene = new THREE.Scene();
    scene.background = new THREE.Color( 0xffffff );
    return scene
}

function setLights(){
    const light = new THREE.AmbientLight(0x404040);
    scene.add(light)

    const pointLight = new THREE.PointLight(0xffffff, 3, 100)
    pointLight.position.set(50, 50, 50)
    const pointLight2 = new THREE.PointLight(0xffffff, 2, 100)
    pointLight2.position.set(-80, 1, 0)
    
    scene.add(pointLight)
    scene.add(pointLight2)
}

function setModel(){
    const loader = new THREE.GLTFLoader();

    loader.load( 'mao.glb', function ( gltf ) {
        gltf.scene.scale.set(0.5,0.5,0.5);

        obj = gltf.scene
        mao = obj.children[0].children[0].children[0].children;
        mao = mao.filter((dedos, index) => {
            return index >= 1 && index <=5;
        })

        scene.add( gltf.scene );

    }, undefined, function ( error ) {
        console.error( error );
    } );
}

function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
        r: parseInt(result[1], 16)/100,
        g: parseInt(result[2], 16)/100,
        b: parseInt(result[3], 16)/100
    } : null;
}

function changeColor(){
    color = hexToRgb(document.getElementById('color').value)
}

function movDedos(){
    for(let i = 1; i<5; i++){
        if(leituraMaoAnterior[i] - leituraMao[i] < 0){
            sentido[i] = 1
        } else if (leituraMaoAnterior[i] - leituraMao[i] > 0){
            sentido[i] = -1
        } 
        
        const position = (Math.abs(leituraMao[i]-100))/100
        
        mao[i].children[0].material.color = color
        rotacaoSuave(position, sentido[i], mao[i])

        leituraMaoAnterior[i] = leituraMao[i]
    }
}

function rotacaoSuave(posicao, sentido, dedo){
    console.log(dedo.rotation.y)
    if(sentido > 0){
        if(dedo.rotation.y > posicao) {
            dedo.rotation.y -= 0.1 // 0.25
            dedo.children[0].rotation.y -= 0.1
            dedo.children[0].children[0].rotation.y -= 0.1
        }
    }
    else if (sentido < 0 ){
        if(dedo.rotation.y < posicao) {
            dedo.rotation.y += 0.1 // 0.25
            dedo.children[0].rotation.y += 0.1
            dedo.children[0].children[0].rotation.y += 0.1
        }
    }
}

function movDedao(){
    if(leituraMao[0] == 0 && mao[0].children[1].rotation.x> -1){
        mov[0] += 0.1
    }
    else if(leituraMao[0] == 100 && mao[0].children[1].rotation.x< 0){
        mov[0] -= 0.1
    }
    mao[0].children[1].material.color = color
    mao[0].children[1].rotation.x = mov[0]*-1
    mao[0].children[1].children[0].rotation.x = mov[0]*-1
}