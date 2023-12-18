import System.IO

type Contato = (String, Int, String, String) -- todo contato é uma tupla com 4 componentes

buscar_dados :: [Contato] -> String -> Contato
buscar_dados [] _ = ("", 0, "", "")
buscar_dados ((nome, tel, ender, relac) : restante_contatos, str)
    | str == nome = (nome, tel, ender, relac)
    | otherwise = buscar_dados(restante_contatos, str)


remover_contato :: [Contato] -> Contato -> [Contato]
remover_contato [] _ = []
remover_contato(contato : restante_contatos, contato_procurado)
    | remover_contato == contato = remover_contato(restante_contatos, contato_procurado)
    | otherwise = contato : remover_contato(restante_contatos, contato_procurado)


existe_contato :: [Contato] -> String -> Bool
existe_contato [] str = False
existe_contato _ "" = False
existe_contato((nome, tel, ender, relac) : restante_contatos, str)
    | nome == str = True
    | otherwise = existe_contato(restante_contatos, str)


editar_contato :: [Contato] -> Contato -> [Contato]
editar_contato [] _ = []
editar_contato contatos contato_atualizado =
    map (\c -> if nome c == nome_atualizado then contato_atualizado else c) contatos
  where
    nome_atualizado = fst contato_atualizado

    
    
inserir_contato :: [Contato] -> Contato -> [Contato]
inserir_contato(contatos, contato)
    | existe_contato(contatos, contato) = editar_contato(contatos, contato)
    | otherwise = contato : contatos


exibir_contatos :: [Contato] -> IO ()
exibir_contatos [] = putStrLn "Nenhum contato cadastrado!"
exibir_contatos contatos = mapM_ exibir_contato contatos


exibir_contato_procurado :: [Contato] -> String -> IO ()
exibir_contato_procurado contatos nome_procurado
    | existe_contato contatos nome_procurado = exibir_contato contato_procurado
    | otherwise = putStrLn "Contato não encontrado!"


exibir_contato :: Contato -> IO ()
exibir_contato (nome, tel, ender, relac) =
    putStrLn $ "Nome: " ++ nome ++ "\nTelefone: " ++ show tel ++ "\nEndereço: " ++ ender ++ "\nRelação: " ++ relac ++ "\n"


gravar_contatos :: [Contato] -> String -> IO ()
gravar_contatos(contatos, nome_arquivo) = do
    withFile nome_arquivo WriteMode $ \arquivo -> do
        hSetEncoding arquivo utf8
        mapM_ (hPutStrLn arquivo . formatar_contato) contatos
    putStrLn "Contatos gravados com sucesso!"


ler_contatos :: String -> IO [Contato]
ler_contatos(nome_arquivo) = do
    conteudo <- readFile nome_arquivo
    let linhas = lines conteudo
    return $ map parse_contato linhas


formatar_contato :: Contato -> String
formatar_contato(nome, tel, ender, relac) =
    nome ++ ";" ++ show tel ++ ";" ++ ender ++ ";" ++ relac


parse_contato :: String -> Contato
parse_contato(linha) = 
    let [nome, tel, ender, relac] = splitOn ";" linha
    in (nome, read tel, ender, relac)
    
main::IO()
main = do

