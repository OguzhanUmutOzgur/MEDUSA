<!DOCTYPE html>


<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <meta charset="utf-8" />
    <link rel="shortcut icon" type="image/x-icon" href="images/iconhytale.ico" />
    <link rel="stylesheet" href="cv.css">
    <link rel="stylesheet" type="text/css" href="css/lightbox.min.css">           <!--L'affichage particulier des -->
    <script type="text/javascript" src="js/lightbox-plus-jquery.min.js"></script> <!-- images dans le page de galerie.-->
    <script type="text/javascript" src="function.js"></script>
    <title>Medusa</title>
</head>

<body>
  <script>
    setInterval(function(){
    window.location.reload(false); /* Rafraichir le page dans chaque 30 secondes pour récuperer les nouvelles données */
    },30000);
  </script>
 
  <div id="all">      <!-- Le page qui est affiché avant de se connecter -->
  <div id="upside">
      <img id="upperbackgroundphoto" src="images/hytale.png"> <!--  Logo de MEDUSA -->

  <a class="login" href="login.php"> Se connecter</a>
       <ul>
  <a class="menü" href="accueil.php">Accueil</a>
  <a class="menü" href="haberler.php">Galerie</a>        <!-- Les buttons des pages (Barre de menu) -->
  <a class="menü" href="iletişim.php">Contact</a>
  <a class="menü" href="hakkında.php">Qui sommes-nous ? </a>
      </ul>

      <div id="body">

              <?php
            $msg = '';
                              echo "<style type='text/css'>
                    #all2{
                        visibility: hidden;
                    }
                   </style>";
            
            if (isset($_POST['login']) && !empty($_POST['username']) && !empty($_POST['password'])) {
        
               if ($_POST['username'] == 'Essai' && $_POST['password'] == '1234') {   /*vérification du mot de passe et de l'id*/
                  $_SESSION['valid'] = true;            
                  echo 'You have entered valid use name and password'; /*Si le mot de passe et l'id sont valide, 
                                                                        faire invisible  le page de se connecter 
                                                                        et faire visible le page d'utilisateur qui est cacher dans le code CSS  */
                  echo "<style type='text/css'>
                    #all{
                        display:none;                             /
                    }
                    #all2{
                    visibility: visible;
                  }    </style>";

               }else {
                  $msg = 'Wrong username or password';                /*Si le mot de passe et l'id ne sont pas valide 
                                                                       afficher une message d'erreur   */
               }
            }
         ?>

        <div class="loginside">

          <form class = "form-signin" role = "form" action = "<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" method = "post">
            <h4 class = "girisbilgileri"><?php echo $msg; ?></h4>
            <input  type = "text" class = "form-control" name = "username" required autofocus></br>
            <input type = "password" class = "form-control" name = "password" required></br>           <!-- Le forme de se connecter -->
            <button class = "loginbutton" type ="submit" name ="login"> Se Connecter </button>

         </form>

        </div> 
      </div>
          
  </div>
</div>
  <div id="all2">           <!-- Le page d'utilisateur qui est affiché aprés de se connecter -->
  <div id="upside">
    
      <img id="upperbackgroundphoto" src="images/hytale.png">

  <a class="login" href="accueil.php">Quitter</a>
      <ul>
  <a class="menü" href="accueil.php">Accueil</a>
  <a class="menü" href="haberler.php">Galerie</a>
  <a class="menü" href="iletişim.php">Contact</a>
  <a class="menü" href="hakkında.php">Qui sommes-nous ? </a>
      </ul>
      
      <div id="body">

<div id="location">
                <?php
      function siteConnect($site)
 {

        $ch = curl_init();
        $hc = "YahooSeeker-Testing/v3.9 (compatible; Mozilla 4.0; MSIE 5.5; Yahoo! Search - Web Search)";
        curl_setopt($ch, CURLOPT_REFERER, 'http://www.google.com');
        curl_setopt($ch, CURLOPT_URL, $site);
        curl_setopt($ch, CURLOPT_USERAGENT, $hc);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);     /* Code php qui s'adresse au lien donnée (172.16.13.4) et récupere
                                                            les  coordonnées qui sont à l'interieur de division "kardech" */
        $site = curl_exec($ch);
        curl_close($ch);
        preg_match_all('@<div id="kardech">(.*?)</div>@si',$site,$veri_derece1);
        echo "<p id='veriveri'".$veri_derece1[0][0];
       }
            
       $giris = siteConnect('172.16.13.4');
       


      ?>
</div>
    
<div id="temperature">
                  <?php
      function siteConnect($site)
 {

        $ch = curl_init();
        $hc = "YahooSeeker-Testing/v3.9 (compatible; Mozilla 4.0; MSIE 5.5; Yahoo! Search - Web Search)";
        curl_setopt($ch, CURLOPT_REFERER, 'http://www.google.com');
        curl_setopt($ch, CURLOPT_URL, $site);
        curl_setopt($ch, CURLOPT_USERAGENT, $hc);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);     /* Code php qui s'adresse au lien donnée (172.16.13.4) et récupere
                                                            le témperature qui sont à l'interieur de division "temperature" */
        $site = curl_exec($ch);
        curl_close($ch);
        

        preg_match_all('@<div id="temperature">(.*?)</div>@si',$site,$veri_derece1);

              
        echo "<p id='veriveri'".$veri_derece1[0][0];
       }
            
       $giris = siteConnect('172.16.13.4');
       


      ?>
  
</div>

<div id="acidite">
                  <?php
      function siteConnect($site)
 {

        $ch = curl_init();
        $hc = "YahooSeeker-Testing/v3.9 (compatible; Mozilla 4.0; MSIE 5.5; Yahoo! Search - Web Search)";
        curl_setopt($ch, CURLOPT_REFERER, 'http://www.google.com');
        curl_setopt($ch, CURLOPT_URL, $site);
        curl_setopt($ch, CURLOPT_USERAGENT, $hc);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);     /* Code php qui s'adresse au lien donnée (172.16.13.4) et récupere
                                                            le valeur de pH qui sont à l'interieur de division "acidite" */
        $site = curl_exec($ch);
        curl_close($ch);
        

        preg_match_all('@<div id="acidite">(.*?)</div>@si',$site,$veri_derece1);

              
        echo "<p id='veriveri'".$veri_derece1[0][0];
       }
            
       $giris = siteConnect('172.16.13.4');
       


      ?>
                         
</div>

<div id="bac">
                      <?php
      function siteConnect($site)
 {

        $ch = curl_init();
        $hc = "YahooSeeker-Testing/v3.9 (compatible; Mozilla 4.0; MSIE 5.5; Yahoo! Search - Web Search)";
        curl_setopt($ch, CURLOPT_REFERER, 'http://www.google.com');
        curl_setopt($ch, CURLOPT_URL, $site);
        curl_setopt($ch, CURLOPT_USERAGENT, $hc);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);     /* Code php qui s'adresse au lien donnée (172.16.13.4) et récupere
                                                            l'état du bac qui sont à l'interieur de division "etatdubac" */
        $site = curl_exec($ch);
        curl_close($ch);
        

        preg_match_all('@<div id="kardech">(.*?)</div>@si',$site,$veri_derece1);

              
        echo "<p id='veriveri'".$veri_derece1[0][0];
       }
            
       $giris = siteConnect('172.16.13.4');
       
 

      ?>
</div>


      
  </div>
  </div>
</body>
</html>







