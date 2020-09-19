# OpenGLTraining

<a alt="C/C++"> <img src="https://img.shields.io/badge/C%2FC%2B%2B17-MSVC-red" /> </a>
<a alt="GLSL"> <img src="https://img.shields.io/badge/GLSL-4.2-red" /> </a>
<a alt="OpenGL"> <img src="https://img.shields.io/badge/OpenGL-gray" /> </a>
<a alt="Glad"> <img src="https://img.shields.io/badge/Glad-gray" /> </a>
<a alt="GLFW"> <img src="https://img.shields.io/badge/GLFW-gray" /> </a>
<a alt="GLM"> <img src="https://img.shields.io/badge/GLM-gray" /> </a>

My adventure to the world of OpenGL. The main goal of this project is to learn OpenGL specification and the basic parts of graphics programming. Here you can find implementations of many common algorithms, which is used in graphics programming. To run this program you should have Visual Studio with preinstalled C/C++ MSVC compiler, all dependencies, which will be mentioned after the ToC.

## Table of Contents

### 1. Start
- <details>
    <summary>First Square</summary>
  
    ![](/Screenshots/1.%20Start/1%20First%20square.png)
  </details>
  
- <details>
    <summary>Textures</summary>
  
    ![](/Screenshots/1.%20Start/2%20Textures.png)
  </details>

- <details>
    <summary>Uniforms</summary>
  
    ![](/Screenshots/1.%20Start/3%20Uniforms.png)
  </details>

- <details>
    <summary>Coordinate system</summary>
  
    ![](/Screenshots/1.%20Start/4%20Coordinate%20system.png)
  </details>

### 2. Lighting
- <details>
    <summary>Basic Lighting (Phong)</summary>
  
    ![](/Screenshots/2.%20Lighting/1.%20Basic%20Lighting%20(%20Phong).png)
  </details>

- <details>
    <summary>Materials</summary>
  
    ![](/Screenshots/2.%20Lighting/2.%20Materials.png)
  </details>

- <details>
    <summary>Lighting Map</summary>
  
    ![](/Screenshots/2.%20Lighting/3.Lighting%20Map.png)
  </details>

- <details>
    <summary>Light Casters</summary>
  
    ![](/Screenshots/2.%20Lighting/4.%20Light%20Casters.png)
  </details>

- <details>
    <summary>Multiple Lights</summary>
  
    ![](/Screenshots/2.%20Lighting/5.%20Multiple%20Lights.png)
  </details>

### 3. Model loading
- <details>
    <summary>Assimp</summary>
  
    ![](/Screenshots/3.%20Model%20Loading/1.%20Assimp.png)
  </details>

### 4. Advanced OpenGL
- <details>
    <summary>Depth test</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/1.%20Depth%20test.png)
  </details>
  
- <details>
    <summary>Stencil Test</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/2.%20Stencil%20Test.png)
  </details>

- <details>
    <summary>Blending</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/3.%20Blending.png)
  </details>

- <details>
    <summary>Face culling</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/4.%20Face%20culling.png)
  </details>

- <details>
    <summary>Framebuffer + PostEffects</summary>
 
    | Sharpen             |  Blur |
    :-------------------------:|:-------------------------:
    ![](/Screenshots/4.%20Advanced%20OpenGL/5.1.%20Framebuffer%20(Sharpen%20Posteffect).png)|![](/Screenshots/4.%20Advanced%20OpenGL/5.2.%20Framebuffer%20(Blur%20Posteffect).png)

    | Edge             |  Grayscale |
    :-------------------------:|:-------------------------:
    ![](/Screenshots/4.%20Advanced%20OpenGL/5.3.%20Framebuffer%20(Edge%20Posteffect).png)|![](/Screenshots/4.%20Advanced%20OpenGL/5.4.%20Framebuffer%20(Grayscale%20Posteffect).png)

    | Inversion |
    :-------------------------:
    ![](/Screenshots/4.%20Advanced%20OpenGL/5.5.%20Framebuffer%20(Inversion%20Posteffect).png)
  </details>

- <details>
    <summary>Cubemap</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/6.%20Cubemap.png)
  </details>

- <details>
    <summary>Exploding</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/7.%20Exploding.png)
  </details>

- <details>
    <summary>GeometryShader</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/8.%20GeometryShader.png)
  </details>

- <details>
    <summary>Instancing</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/9.%20Instancing.png)
  </details>

- <details>
    <summary>AntiAliasing</summary>
  
    ![](/Screenshots/4.%20Advanced%20OpenGL/10.%20AntiAliasing.png)
  </details>

### 5. Advanced Lighting
- <details>
    <summary>Advanced Lighting (Blinn-Phong)</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/1.%20Advanced%20Lighting%20(Blinn-Phong).png)
  </details>
  
- <details>
    <summary>Gamma Correction</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/2.%20Gamma%20Correction.png)
  </details>

- <details>
    <summary>Shadow Mapping</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/3.%20Shadow%20Mapping.png)
  </details>

- <details>
    <summary>Point Shadows</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/4.%20Point%20Shadows.png)
  </details>

- <details>
    <summary>Normal Mapping</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/5.%20Normal%20Mapping.png)
  </details>

- <details>
    <summary>Parallax + Normal Mapping</summary>
  
    ![](/Screenshots/5.%20Advanced%20Lighting/6.%20Parallax%20+%20Normal%20Mapping.png)
  </details>

- <details>
    <summary>HDR</summary>
  
    | Without HDR              |  With HDR |
    :-------------------------:|:-------------------------:
    ![](/Screenshots/5.%20Advanced%20Lighting/7.1.%20Without%20hdr.png)|![](/Screenshots/5.%20Advanced%20Lighting/7.2%20With%20hdr%20(reinhard%20%20exposure).png)
  </details>

- <details>
    <summary>Bloom</summary>
 
    ![](/Screenshots/5.%20Advanced%20Lighting/8.%20Bloom%20(with%20Gaussian%20blur).png)
  </details>
  
- <details>
    <summary>Deferred shading</summary>
    
    ![](Screenshots/5.%20Advanced%20Lighting/9.4.%20Deffered%20Shading.png)
    
    | GBuffer-Position             |  GBuffer-Normal | GBuffer-AlbedoSpecular|
    :-------------------------:|:-------------------------:|:-------------------------:
    ![](Screenshots/5.%20Advanced%20Lighting/9.1.%20GBuffer-Position.png)|![](Screenshots/5.%20Advanced%20Lighting/9.2.%20GBuffer-Normal.png)|![](Screenshots/5.%20Advanced%20Lighting/9.3.%20GBuffer-AlbegoSpecular.png)
  </details>
- <details>
    <summary>SSAO</summary>
    
    ![](Screenshots/5.%20Advanced%20Lighting/10.%20SSAO.png)
  </details>

### 5. PBR (Physically based rendering)
- <details>
    <summary>Basic Light</summary>
  
    | Without HDR and Gamma correction             |  With HDR and Gamma correction | With maps |
    :-------------------------:|:-------------------------:|:-------------------------:
    ![](Screenshots/6.%20PBR/1.1%20Wothout%20HDR%20and%20Gamma%20Correction.png)|![](Screenshots/6.%20PBR/1.3%20With%20HDR%20and%20Gamma%20Correction.png)|![](Screenshots/6.%20PBR/1.4%20With%20Maps.png)
  </details>
  
- <details>
    <summary>Diffusal and Specular Image Based Lighting</summary>
  
    | Diffusal IBL             |  Diffusal and Specular IBL |
    :-------------------------:|:-------------------------:
    ![](Screenshots/6.%20PBR/2.1.DiffusalIBL.png)|![](Screenshots/6.%20PBR/2.2.SpecularIBL.png)
  </details>
  


## Dependencies

1. [Glad](https://glad.dav1d.de)
2. [Glfw](https://www.glfw.org)
3. [Glm](https://glm.g-truc.net/0.9.9/index.html)
4. [Stb](https://github.com/nothings/stb)
5. [Assimp](https://www.assimp.org)

### Apache 2.0 license synopsis

The Apache 2.0 license is a permissive free software license by the Apache Software Foundation. The 2.0 version requires preservation of the copyright notice and disclaimer. It also allows the user of the software the freedom to use the software for any purpose, modify it, and distribute the modified versions of the software, under the terms of the license, without concern for royalties.

Key points:
```markdown
1. Keep the copyright notice.
2. Your software has to contain a copy of the Apache 2.0 license.
3. You are free to use, modify, distribute, and redistribute the software.
4. If you modify the code, you have to mention your modifications particularly.
5. If there is a text file called NOTICE, take time and read it. It contains further information about the specific parts of the license and the purpose of the software.
6. The NOTICE file has to be included in your software release too.
```

More information on about the Apache 2.0 license can be found [here](https://choosealicense.com/licenses/apache-2.0).
