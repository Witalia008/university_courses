Rails.application.routes.draw do
  match 'index' => 'general#index', :via => [:get], :as => 'index'
  match 'about' => 'general#about', :via => [:get], :as => 'about'
  match 'search' => 'general#search', :via => [:get], :as => 'search'

  match 'signup' => 'users#new', :via => [:get], :as => 'signup'
  match 'login' => 'sessions#login', :via => [:get], :as => 'login'
  match 'logout' => 'sessions#logout', :via => [:get], :as => 'logout'
  post 'sessions/login_attempt'
  match 'home' => 'sessions#home', :via => [:get], :as => 'home'

  get 'contact', to: 'messages#new', as: 'contact'
  post 'contact', to: 'messages#create'

  resources :users do
    get 'trolley', to: 'orders#trolley', as: 'trolley'
    patch 'trolley/pay', to: 'orders#trolley_pay', as: 'pay_trolley'
    get 'orders', to: 'orders#show', as: 'orders'

    delete 'order/:id', to: 'orders#destroy', as: 'order'
  end
  resources :news
  get 'news_old', to: 'news#index_old', as: 'news_old'
  resources :groups do
    get 'new', to: 'groups#new'
    post '', to: 'groups#create', as: 'create_sub'

    resources :items do
      post 'order', to: 'orders#create', as: 'order'
    end
  end

  root 'general#index'

  # The priority is based upon order of creation: first created -> highest priority.
  # See how all your routes lay out with "rake routes".

  # You can have the root of your site routed with "root"
  # root 'welcome#index'

  # Example of regular route:
  #   get 'products/:id' => 'catalog#view'

  # Example of named route that can be invoked with purchase_url(id: product.id)
  #   get 'products/:id/purchase' => 'catalog#purchase', as: :purchase

  # Example resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Example resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Example resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Example resource route with more complex sub-resources:
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', on: :collection
  #     end
  #   end

  # Example resource route with concerns:
  #   concern :toggleable do
  #     post 'toggle'
  #   end
  #   resources :posts, concerns: :toggleable
  #   resources :photos, concerns: :toggleable

  # Example resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end
end
